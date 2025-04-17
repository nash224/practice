#pragma once

#ifndef __DEFINE_HEADER_H
#define __DEFINE_HEADER_H

#define MY_STL my_stl::


#define safe_delete(x) if(nullptr != x) delete x; x = nullptr;
#define safe_array_delete(x) if(nullptr != x) delete[] x; x = nullptr;

#endif // !__DEFINE_HEADER_H

