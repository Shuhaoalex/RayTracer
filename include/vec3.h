#ifndef VEC3_H
#define VEC3_H
#include <Eigen/Dense>
//dense types
using vec3 = Eigen::Vector3d;
using point3 = vec3;
using color = vec3;

inline vec3 random_vec3(double min, double max) {
	return (max - min) / 2 * (vec3::Random().array() + 1) + min;
}

inline vec3 random_in_unit_sphere() {
	while (true) {
		vec3 p = vec3::Random();
		if (p.squaredNorm() >= 1) continue;
		return p;
	}
}

inline vec3 random_unit_vector() {
	return random_in_unit_sphere().normalized();
}

inline vec3 random_in_unit_disk() {
	while (true) {
		vec3 p = vec3::Random();
		p[2] = 0;
		if (p.squaredNorm() >= 1) continue;
		return p;
	}
}

inline bool near_zero(vec3 a) {
	const auto s = 1e-8;
	return a.cwiseAbs().maxCoeff() < s;
}

inline vec3 reflect(const vec3& v, const vec3& n) {
	return v - 2 * v.dot(n) * n;
}

inline vec3 refract(const vec3& uv, const vec3& n, double etai_over_etat) {
	auto cos_theta = fmin(-n.dot(uv), 1.0);
	vec3 r_out_prep = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0 - r_out_prep.squaredNorm())) * n;
	return r_out_prep + r_out_parallel;
}

#endif