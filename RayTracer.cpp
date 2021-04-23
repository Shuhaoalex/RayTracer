// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <omp.h>
#include "material.h"
#include "utils.h"
#include "hittable_list.h"
#include "write_ppm.h"
#include "sphere.h"
#include "moving_sphere.h"
#include "camera.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;


color ray_color(const ray& r, const hittable& world, int depth) {
	if (depth <= 0) return color(0, 0, 0);
	hit_record rec;
	if (world.hit(r, 1e-4, infinity, rec)) {
		ray scattered;
		color attenuation;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation.cwiseProduct(ray_color(scattered, world, depth - 1));
		return color(0, 0, 0);
	}
	vec3 unit_direction = r.direction.normalized();
	auto t = 0.5 * (unit_direction[1] + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

hittable_list random_scene() {
	hittable_list world;

	auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
	world.add(make_shared<sphere>(point3(0, -1000, 0), 1000, ground_material));

	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			auto choose_mat = random_double();
			point3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

			if ((center - point3(4, 0.2, 0)).norm() > 0.9) {
				shared_ptr<material> sphere_material;

				if (choose_mat < 0.8) {
					// diffuse
					color albedo = vec3::Random().cwiseProduct(vec3::Random());
					sphere_material = make_shared<lambertian>(albedo);
					vec3 center2 = center + vec3(0, random_double(0, .5), 0); // The datatype here for center2 must be vec3 and should not be auto! otherwise center2 will not be evaluated
					world.add(make_shared<moving_sphere>(center, center2, 0.0, 1.0, 0.2, sphere_material));
				}
				else if (choose_mat < 0.95) {
					// metal
					color albedo = random_vec3(0.5, 1);
					auto fuzz = random_double(0, 0.5);
					sphere_material = make_shared<metal>(albedo, fuzz);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
				else {
					// glass
					sphere_material = make_shared<dielectric>(1.5);
					world.add(make_shared<sphere>(center, 0.2, sphere_material));
				}
			}
		}
	}

	auto material1 = make_shared<dielectric>(1.5);
	world.add(make_shared<sphere>(point3(0, 1, 0), 1.0, material1));

	auto material2 = make_shared<lambertian>(color(0.4, 0.2, 0.1));
	world.add(make_shared<sphere>(point3(-4, 1, 0), 1.0, material2));

	auto material3 = make_shared<metal>(color(0.7, 0.6, 0.5), 0.0);
	world.add(make_shared<sphere>(point3(4, 1, 0), 1.0, material3));

	return world;
}

int main()
{
	// Image
	const double aspect_ratio = 16.0 / 9.0;
	const size_t width = 400;
	const size_t height = static_cast<size_t>(width / aspect_ratio);
	const size_t samples_per_pixel = 100;
	const int max_depth = 50;

	// World
	auto world = random_scene();
	
	//Camera
	point3 lookfrom(13, 2, 3);
	point3 lookat(0, 0, 0);
	vec3 vup(0, 1, 0);
	auto dist_to_focus = 10.0;
	auto aperture = 0.1;
	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

	// Render

	size_t num_chnls = 3;
	std::vector<unsigned char> tmp(width * height * num_chnls);

	auto start = high_resolution_clock::now();

	#pragma omp parallel for schedule(dynamic)
	for (int j = height - 1; j >= 0; --j) {
		#pragma omp critical
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (size_t i = 0; i < width; ++i) {
			color pix_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (width - 1);
				auto v = (j + random_double()) / (height - 1);
				ray r = cam.get_ray(u, v);
				pix_color += ray_color(r, world, max_depth);
			}
			pix_color /= samples_per_pixel;
			fill_color(tmp, width, height, i, height - j - 1, pix_color);
		}
	}
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<seconds>(stop - start);
	std::cout << duration.count() << std::endl;
	write_ppm("result.ppm", tmp, width, height);
}