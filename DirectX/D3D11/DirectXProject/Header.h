#pragma once

#ifndef __DEFINE_HEADER_H_
#define __DEFINE_HEADER_H_

#define safe_delete(x) if (nullptr != x) delete x; x = nullptr;

#define MessageBoxAssert(msg) MessageBox(0, msg, 0, MB_OK | MB_ICONEXCLAMATION);

#endif // !__DEFINE_HEADER_H_
