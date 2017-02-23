#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>

#include "OpenCL/cl.hpp"

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

//#define TARGET_WIDTH 3840
//#define TARGET_HEIGHT 2160
//#define TARGET_WIDTH 1920
//#define TARGET_HEIGHT 1080
#define TARGET_WIDTH 1280
#define TARGET_HEIGHT 720
//#define TARGET_WIDTH 320
//#define TARGET_HEIGHT 180

typedef struct __attribute__ ((packed)) td_Sphere {
	cl_float4 position;
	cl_float4 emission;
	cl_float4 diffuse_color;
	cl_float radius;
	cl_float crap1;
	cl_float crap2;
	cl_float crap3;
} Sphere;

typedef struct __attribute__ ((packed)) td_Triangle {
	cl_float4 vertices[3];
} Triangle;

int main() {
	// get all platforms (drivers), e.g. NVIDIA
	std::vector<cl::Platform> all_platforms;
	cl::Platform::get(&all_platforms);

	if (all_platforms.size() == 0) {
		std::cout << " No platforms found. Check OpenCL installation!\n";
		exit(1);
	}
	cl::Platform default_platform = all_platforms[0];
	std::cout << "Using platform: " << default_platform.getInfo<CL_PLATFORM_NAME>() << "\n";

	// get default device (CPUs, GPUs) of the default platform
	std::vector<cl::Device> all_devices;
	default_platform.getDevices(CL_DEVICE_TYPE_ALL, &all_devices);
	if (all_devices.size() == 0) {
		std::cout << " No devices found. Check OpenCL installation!\n";
		exit(1);
	}

	// use device[1] because that's a GPU; device[0] is the CPU
	cl::Device default_device = all_devices[1];
	std::cout << "Using device: " << default_device.getInfo<CL_DEVICE_NAME>() << "\n";

	// a context is like a "runtime link" to the device and platform;
	// i.e. communication is possible
	cl::Context context({default_device});

	// create the program that we want to execute on the device
	cl::Program::Sources sources;

	std::ifstream source_file("kernel.cl");
	std::stringstream kernel_source;
	kernel_source << source_file.rdbuf();
	std::string s = kernel_source.str();

	sources.push_back({s.c_str(), s.length()});

	cl::Program program(context, sources);
	if (program.build({default_device}) != CL_SUCCESS) {
		std::cout << "Error building: " << program.getBuildInfo<CL_PROGRAM_BUILD_LOG>(default_device) << std::endl;
		exit(1);
	}

	int image_width = TARGET_WIDTH;
	int image_height = TARGET_HEIGHT;

	cl_int n_spheres = 9;
	Sphere spheres[n_spheres];

	// left sphere
	spheres[6].radius = 0.16f;
	spheres[6].position = cl_float3{-0.25f, -0.24f, -1.0f};
	spheres[6].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[6].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// right sphere
	spheres[7].radius = 0.16f;
	spheres[7].position = cl_float3{0.25f, -0.24f, -0.6f};
	spheres[7].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[7].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// lightsource
	spheres[5].radius = 0.3f;
	spheres[5].position = cl_float3{0.0f, 0.75f, -1.0f};
	spheres[5].diffuse_color = cl_float3{0.0f, 0.0f, 0.0f};
	spheres[5].emission = cl_float3{19.0f, 18.0f, 17.0f};

	spheres[0].radius = 200.0f;
	spheres[0].position = cl_float3{-201.6f, 0.0f, 0.0f};
	spheres[0].diffuse_color = cl_float3{0.75f, 0.25f, 0.25f};
	spheres[0].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// right wall
	spheres[1].radius = 200.0f;
	spheres[1].position = cl_float3{201.6f, 0.0f, -1.0f};
	spheres[1].diffuse_color = cl_float3{0.25f, 0.25f, 0.75f};
	spheres[1].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// floor
	spheres[2].radius = 200.0f;
	spheres[2].position = cl_float3{0.0f, -200.4f, -1.0f};
	spheres[2].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[2].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// ceiling
	spheres[3].radius = 200.0f;
	spheres[3].position = cl_float3{0.0f, 201.4f, -1.0f};
	spheres[3].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[3].emission = cl_float3{0.0f, 0.0f, 0.0f};

	// back wall
	spheres[4].radius = 200.0f;
	spheres[4].position = cl_float3{0.0f, 0.0f, -202.4f};
	spheres[4].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[4].emission = cl_float3{0.0f, 0.0f, 0.0f};

	/// front wall
	spheres[8].radius = 200.0f;
	spheres[8].position = cl_float3{.0f, 0.0f, 201.0f};
	spheres[8].diffuse_color = cl_float3{0.9f, 0.8f, 0.7f};
	spheres[8].emission = cl_float3{0.0f, 0.0f, 0.0f};

	cl_int n_triangles = 1;
	Triangle triangles[1] = {{{{-10.0f, -10.0f, 10.0f}, {-10.0f, -10.0f, -100.0f}, {-10.0f, 10.0f, -100.0f}}}};

	int pixel_count = image_height * image_width;
	int seed = rand();

// create buffers on device (allocate space on GPU)
	cl::Buffer buffer_image_width(context, CL_MEM_READ_WRITE, sizeof(int));
	cl::Buffer buffer_image_height(context, CL_MEM_READ_WRITE, sizeof(int));
	cl::Buffer buffer_image(context, CL_MEM_READ_WRITE, sizeof(char) * pixel_count * 4);
	cl::Buffer buffer_spheres(context, CL_MEM_READ_WRITE, sizeof(Sphere) * n_spheres);
	cl::Buffer buffer_nspheres(context, CL_MEM_READ_WRITE, sizeof(cl_int));
	cl::Buffer buffer_triangles(context, CL_MEM_READ_WRITE, sizeof(Triangle) * n_triangles);
	cl::Buffer buffer_ntriangles(context, CL_MEM_READ_WRITE, sizeof(cl_int));
	cl::Buffer buffer_seed(context, CL_MEM_READ_WRITE, sizeof(int));

// create a queue (a queue of commands that the GPU will execute)
	cl::CommandQueue queue(context, default_device);

// push write commands to queue
	queue.enqueueWriteBuffer(buffer_image_width, CL_TRUE, 0, sizeof(int), &image_width);
	queue.enqueueWriteBuffer(buffer_image_height, CL_TRUE, 0, sizeof(int), &image_height);
	queue.enqueueWriteBuffer(buffer_spheres, CL_TRUE, 0, sizeof(Sphere) * n_spheres, spheres);
	queue.enqueueWriteBuffer(buffer_nspheres, CL_TRUE, 0, sizeof(cl_int), &n_spheres);
	queue.enqueueWriteBuffer(buffer_triangles, CL_TRUE, 0, sizeof(Triangle) * n_triangles, triangles);
	queue.enqueueWriteBuffer(buffer_ntriangles, CL_TRUE, 0, sizeof(cl_int), &n_triangles);
	queue.enqueueWriteBuffer(buffer_seed, CL_TRUE, 0, sizeof(int), &seed);

	cl::Kernel simple_add(program, "render_image");
	simple_add.setArg(0, buffer_image_width);
	simple_add.setArg(1, buffer_image_height);
	simple_add.setArg(2, buffer_image);
	simple_add.setArg(3, buffer_spheres);
	simple_add.setArg(4, buffer_nspheres);
	simple_add.setArg(5, buffer_triangles);
	simple_add.setArg(6, buffer_ntriangles);
	simple_add.setArg(7, buffer_seed);

	queue.finish();

	int *image = new int[pixel_count];

/*std::cout << "result: {";
for (int i = 0; i < pixel_count * 4; i++) {
	std::cout << image[i] << " ";
}
std::cout << "}" << std::endl;
*/


	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Raytracing", sf::Style::Default);
	window.setVerticalSyncEnabled(true);

	sf::Image *output = new sf::Image;
	sf::Texture tex;
	output->create(TARGET_WIDTH, TARGET_HEIGHT, (sf::Uint8 *) image);
	tex.loadFromImage(*output);

	sf::Sprite sprite(tex);

	sprite.setPosition(0, 0);
	sprite.setTexture(tex);
	sprite.setScale((float) WINDOW_WIDTH / TARGET_WIDTH, (float) WINDOW_HEIGHT / TARGET_HEIGHT);

	float t;
	float avg = 0;
	int frames = 0;
	int fileIndex = 0;


	/*t = 0.5;
	spheres[0].position.x = std::sin(t) * 1.5f;
	spheres[0].position.y = std::sin(t * 2.0f) * 1.5f;
	spheres[0].position.z = (std::cos(t * 2.0f) * 1.0f) - 3.0f;

	spheres[1].position.x = std::sin(t) * 1.5f + 2.0f;q
	spheres[1].position.z = std::cos(t) * 1.5f - 4.0f;*/
	queue.enqueueWriteBuffer(buffer_spheres, CL_TRUE, 0, sizeof(Sphere) * n_spheres, spheres);

	sf::Clock timer;
	for (int i = 0; i < 8; ++i) {
		timer.restart();
		seed = rand();
		queue.enqueueWriteBuffer(buffer_seed, CL_TRUE, 0, sizeof(int), &seed);


		queue.enqueueNDRangeKernel(simple_add, cl::NullRange, cl::NDRange(pixel_count), cl::NDRange(128));
		queue.finish();
		std::cout << timer.getElapsedTime().asMilliseconds();
		sleep(2);
	}
	queue.enqueueReadBuffer(buffer_image, CL_TRUE, 0, sizeof(char) * pixel_count * 4, image);

	output->create(TARGET_WIDTH, TARGET_HEIGHT, (sf::Uint8 *) image);
	//output->flipVertically();

	output->saveToFile("out/i" + std::to_string(fileIndex) + ".bmp");
	std::cout << "File saved #" << fileIndex << "\n";
	++fileIndex;

	tex.update(*output);

	while (window.isOpen()) {

		frames++;
		t += 0.033;//timer.getElapsedTime().asSeconds();
		avg += (timer.getElapsedTime().asMilliseconds() - avg) / frames;
		timer.restart();

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Q) {
					exit(0);
				}
			}
		}

		window.draw(sprite);

		window.display();
	}

	std::cout << avg << "\n";

	return 0;
}