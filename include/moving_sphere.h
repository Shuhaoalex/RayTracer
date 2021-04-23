#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "utils.h"
#include "hittable.h"

class moving_sphere : public hittable {
public:
	point3 center0, center1;
	double time0, time1;
	double radius;
	shared_ptr<material> mat_ptr;
public:
	moving_sphere() {}
	moving_sphere(
		point3 cen0, point3 cen1, double _time0, double _time1, double r, shared_ptr<material> m
	) : center0(cen0), center1(cen1), time0(_time0), time1(_time1), radius(r), mat_ptr(m) {};

	virtual bool hit(
		const ray& r,
		double t_tim,
		double t_max,
		hit_record& rec
	) const override;

	point3 center(double time) const;
};

point3 moving_sphere::center(double time) const {
	return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool moving_sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const {
	point3 curr_center = center(r.time);
	vec3 oc = r.origin - curr_center;
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
	vec3 outward_normal = (rec.p - curr_center) / radius;
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

#endif