// RayTracer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Eigen/Dense>
#include <omp.h>
#include <vector>
#include "utils.h"

double hit_sphere(const point3& center, double radius, const ray& r) {
	vec3 oc = r.origin - center;
	double a = r.direction.squaredNorm();
	double b = oc.dot(r.direction);
	double c = oc.squaredNorm()- radius * radius;
	double discriminant = b * b - a * c;
	if (discriminant < 0) {
		return -1.0;
	}
	else {
		return (-b - sqrt(discriminant)) / a;
	}
}

color ray_color(const ray& r) {
	point3 center(0, 0, -1);
	double t = hit_sphere(center, 0.5, r);
	if (t > 0.0) {
		vec3 N = (r.at(t) - center).normalized();
		return 0.5 * color(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = r.direction.normalized();
	t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
	// Image
	const double aspect_ratio = 16.0 / 9.0;
	size_t width = 400;
	size_t height = static_cast<size_t>(width / aspect_ratio);
	
	//Camera

	double viewport_height = 2.0;
	double viewport_width = aspect_ratio * viewport_height;
	double focal_length = 1.0;

	point3 origin = point3(0, 0, 0);
	vec3 horizontal = vec3(viewport_width, 0, 0);
	vec3 vertical = vec3(0, viewport_height, 0);
	vec3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Render

	size_t num_chnls = 3;
	std::vector<unsigned char> tmp(width * height * num_chnls);
	for (size_t j = 0; j < height; ++j) {
		std::cerr << "\rScanlines remaining: " << height - j << ' ' << std::flush;
		for (size_t i = 0; i < width; ++i) {
			size_t curr_idx = (j * width + i) * 3;
			double u = double(i) / (width - 1);
			double v = double(height - j) / (height - 1);
			ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
			color pix_color = ray_color(r);

			tmp[curr_idx] = static_cast<unsigned char>(255.999 * pix_color[0]);
			tmp[curr_idx + 1] = static_cast<unsigned char>(255.999 * pix_color[1]);
			tmp[curr_idx + 2] = static_cast<unsigned char>(255.999 * pix_color[2]);
		}
	}
	write_ppm("result.ppm", tmp, width, height, num_chnls);
}