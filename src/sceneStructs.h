#pragma once

#include <string>
#include <vector>
#include <cuda_runtime.h>
#include "glm/glm.hpp"

#define BACKGROUND_COLOR (glm::vec3(0.0f))

enum GeomType {
    SPHERE,
    CUBE,
    MESH,
};

enum MatType {
    DIFFUSE,
    SPEC_GLASS,
    SPEC_REFL,
    SPEC_TRANS,
    PLASTIC,
};

struct Ray {
    glm::vec3 origin;
    glm::vec3 direction;
};

struct Triangle {
    glm::vec3 v[3];
    glm::vec3 n[3];       
    glm::vec2 uv[3];
    glm::vec3 centroid;
    int geomIdx;
};

struct AABB {
    glm::vec3 min;
    glm::vec3 max;
};

struct BVHNode
{
    glm::vec3 aabbMin, aabbMax;
    int leftNode, firstTriIdx, triCount;
};

struct Geom {
    enum GeomType type;
    int materialid;
    glm::vec3 translation;
    glm::vec3 rotation;
    glm::vec3 scale;
    glm::mat4 transform;
    glm::mat4 inverseTransform;
    glm::mat4 invTranspose;

    int triIdx = -1;
    int triCnt = 0;
    AABB aabb;
};

struct Material {
    MatType type;
    glm::vec3 color;
    struct {
        float exponent;
        glm::vec3 color;
    } specular;
    float hasReflective;
    float hasRefractive;
    float indexOfRefraction;
    float emittance;
};

struct Camera {
    glm::ivec2 resolution;
    glm::vec3 position;
    glm::vec3 lookAt;
    glm::vec3 view;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec2 fov;
    glm::vec2 pixelLength;
};

struct RenderState {
    Camera camera;
    unsigned int iterations;
    int traceDepth;
    std::vector<glm::vec3> image;
    std::string imageName;
};

struct PathSegment {
    Ray ray;
    glm::vec3 L;
    glm::vec3 throughput;
    int pixelIndex;
    int remainingBounces;
    bool specularBounce;
};

// Use with a corresponding PathSegment to do:
// 1) color contribution computation
// 2) BSDF evaluation: generate a new ray
struct ShadeableIntersection {
  float t;
  glm::vec3 surfaceNormal;
  int materialId;
};
