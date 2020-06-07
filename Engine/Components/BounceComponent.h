#pragma once

// saw something like this somewhere but dont remeber how it was implemented
//union {
//	typedef struct {
//		float x;
//		float y;
//	} vector2;
//	float vector2[2];
//};

typedef struct {
	float x;
	float y;
} vector2;

typedef struct {
	vector2 velocity;
} BounceComponent;
