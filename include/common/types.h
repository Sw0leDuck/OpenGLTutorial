#ifndef TYPES_H
#define TYPES_H

typedef unsigned uint;
static_assert(sizeof(uint) == 4, "uint is not 4 bytes");

typedef unsigned char ubyte;
static_assert(sizeof(ubyte) == 1, "ubyte is not 1 bytes");

typedef char byte;
static_assert(sizeof(byte) == 1, "byte is not 1 bytes");

typedef unsigned long long ull;
static_assert(sizeof(ull) == 8, "ull is not 8 bytes");

typedef unsigned short ushort;
static_assert(sizeof(ushort) == 2, "ushort is not 2 bytes");

enum ProgramType : uint {
    kDefault = 0,
    kLast = kDefault
};

#endif