#pragma once

#include "AppleMIDI_Namespace.h"

BEGIN_APPLEMIDI_NAMESPACE

struct IPAddress
{
	char host[100];
	IPAddress() { host[0] = '\0'; }
	IPAddress(const char* host) { operator=(host); }
	operator const char*() { return host; }
	void operator =(const char* host) { strncpy(this->host, host, sizeof(this->host)); }
};

inline unsigned long millis()
{
    auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return (unsigned long)now;
}

inline int random(int min, int max)
{
	return RAND_MAX % std::rand() % (max-min) + min;
}

inline void randomSeed(float)
{
    srand(static_cast<unsigned int>(time(0)));
}

inline size_t min(size_t a, size_t b)
{
	return a > b ? b : a;
}

END_APPLEMIDI_NAMESPACE
