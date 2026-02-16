#pragma once

#include <math.h>

typedef struct {
    float m[4][4];
} Mat4;

static inline void MatIdentity(Mat4* out)
{
    out->m[0][0] = 1.0f; out->m[0][1] = 0.0f; out->m[0][2] = 0.0f; out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f; out->m[1][1] = 1.0f; out->m[1][2] = 0.0f; out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f; out->m[2][1] = 0.0f; out->m[2][2] = 1.0f; out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f; out->m[3][1] = 0.0f; out->m[3][2] = 0.0f; out->m[3][3] = 1.0f;
}

static inline void MatTranspose(Mat4* out, const Mat4* in)
{
    Mat4 tmp;
    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            tmp.m[i][j] = in->m[j][i];
    *out = tmp;
}

static inline void MatPerspectiveFovLH(Mat4* out, float fovY, float aspect, float zn, float zf)
{
    float yScale = 1.0f / tanf(fovY / 2.0f);
    float xScale = yScale / aspect;

    out->m[0][0] = xScale; out->m[0][1] = 0.0f;   out->m[0][2] = 0.0f;              out->m[0][3] = 0.0f;
    out->m[1][0] = 0.0f;   out->m[1][1] = yScale;  out->m[1][2] = 0.0f;              out->m[1][3] = 0.0f;
    out->m[2][0] = 0.0f;   out->m[2][1] = 0.0f;    out->m[2][2] = zf / (zf - zn);    out->m[2][3] = 1.0f;
    out->m[3][0] = 0.0f;   out->m[3][1] = 0.0f;    out->m[3][2] = -zn*zf / (zf - zn); out->m[3][3] = 0.0f;
}

static inline void MatLookAtLH(Mat4* out, const vector3* eye, const vector3* at, const vector3* up)
{
    float zx = at->x - eye->x;
    float zy = at->y - eye->y;
    float zz = at->z - eye->z;
    float zlen = sqrtf(zx*zx + zy*zy + zz*zz);
    zx /= zlen; zy /= zlen; zz /= zlen;

    float xx = up->y * zz - up->z * zy;
    float xy = up->z * zx - up->x * zz;
    float xz = up->x * zy - up->y * zx;
    float xlen = sqrtf(xx*xx + xy*xy + xz*xz);
    xx /= xlen; xy /= xlen; xz /= xlen;

    float yx = zy * xz - zz * xy;
    float yy = zz * xx - zx * xz;
    float yz = zx * xy - zy * xx;

    out->m[0][0] = xx;  out->m[0][1] = yx;  out->m[0][2] = zx;  out->m[0][3] = 0.0f;
    out->m[1][0] = xy;  out->m[1][1] = yy;  out->m[1][2] = zy;  out->m[1][3] = 0.0f;
    out->m[2][0] = xz;  out->m[2][1] = yz;  out->m[2][2] = zz;  out->m[2][3] = 0.0f;
    out->m[3][0] = -(xx*eye->x + xy*eye->y + xz*eye->z);
    out->m[3][1] = -(yx*eye->x + yy*eye->y + yz*eye->z);
    out->m[3][2] = -(zx*eye->x + zy*eye->y + zz*eye->z);
    out->m[3][3] = 1.0f;
}

static inline void MatRotationYawPitchRoll(Mat4* out, float yaw, float pitch, float roll)
{
    float cy = cosf(yaw),   sy = sinf(yaw);
    float cp = cosf(pitch), sp = sinf(pitch);
    float cr = cosf(roll),  sr = sinf(roll);

    out->m[0][0] = cr*cy + sr*sp*sy;   out->m[0][1] = sr*cp;   out->m[0][2] = -cr*sy + sr*sp*cy;  out->m[0][3] = 0.0f;
    out->m[1][0] = -sr*cy + cr*sp*sy;  out->m[1][1] = cr*cp;   out->m[1][2] = sr*sy + cr*sp*cy;   out->m[1][3] = 0.0f;
    out->m[2][0] = cp*sy;              out->m[2][1] = -sp;     out->m[2][2] = cp*cy;              out->m[2][3] = 0.0f;
    out->m[3][0] = 0.0f;               out->m[3][1] = 0.0f;    out->m[3][2] = 0.0f;               out->m[3][3] = 1.0f;
}

static inline void Vec3TransformCoord(vector3* out, const vector3* v, const Mat4* mat)
{
    float x = v->x, y = v->y, z = v->z;
    float w = x * mat->m[0][3] + y * mat->m[1][3] + z * mat->m[2][3] + mat->m[3][3];

    out->x = (x * mat->m[0][0] + y * mat->m[1][0] + z * mat->m[2][0] + mat->m[3][0]) / w;
    out->y = (x * mat->m[0][1] + y * mat->m[1][1] + z * mat->m[2][1] + mat->m[3][1]) / w;
    out->z = (x * mat->m[0][2] + y * mat->m[1][2] + z * mat->m[2][2] + mat->m[3][2]) / w;
}
