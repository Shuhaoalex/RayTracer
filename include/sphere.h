#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	point3 center = vec3(0, 0, 0);
	double radius = 0;
	shared_ptr<material> mat_ptr;
public:
	sphere() {}
	sphere(point3 cen, double r, shared_ptr<material> m) :center(cen), radius(r), mat_ptr(m){};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere :: hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	auto oc = r.origin - center;
	auto a = r.direction.squaredNorm();
	auto half_b = r.direction.dot(oc);
	auto c = oc.squaredNorm() - radius * radius;

	auto discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	auto sqrtd = sqrt(discriminant);

	// Looking for root lies in the acceptable range.
	auto root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.set_face_normal(r, (rec.p - center) / radius);
	rec.mat_ptr = mat_ptr;
	return true;
}

#endif