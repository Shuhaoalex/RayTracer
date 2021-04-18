#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include "vec3.h"

class sphere : public hittable {
public:
	point3 center = vec3(0, 0, 0);
	double radius = 0;
public:
	sphere() {}
	sphere(point3& cen, double r) :center(cen), radius(r) {};

	virtual bool hit(
		const ray& r, double t_min, double t_max, hit_record& rec) const override;
};

bool sphere :: hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	vec3 oc = r.origin - center;
	double a = r.direction.squaredNorm();
	double half_b = r.direction.dot(oc);
	double c = oc.squaredNorm() - radius * radius;

	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0) return false;
	double sqrtd = sqrt(discriminant);

	// Looking for root lies in the acceptable range.
	double root = (-half_b - sqrtd) / a;
	if (root < t_min || t_max < root) {
		root = (-half_b + sqrtd) / a;
		if (root < t_min || t_max < root)
			return false;
	}

	rec.t = root;
	rec.p = r.at(rec.t);
	rec.set_face_normal(r, (rec.p - center) / radius);
	return true;
}

#endif