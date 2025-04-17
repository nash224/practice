// ExceptionSafety.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <mutex>

#define EXCEPT_SAFETY_CODE 1

// 임의로 지정한 눈속임용 타입
using pixel_type = void*;

// 입력 버퍼에 있는 데이터를 가져옵니다.
// 예외 발생 시, unexcept함수가 호출됩니다.
pixel_type read(std::istream& _ImgSrc) throw()
{
	return pixel_type();
}

struct Image 
{
	Image(pixel_type _t) {}
};

// Thread Safe class
// 예외 안전성을 확보하는 일은 프로그래머로서 수행해야 할 덕목
class PrettyMenu
{
public:
	// 배경화면을 업데이트합니다.
	void ChangeBackGround(std::istream& _ImgSrc);

private:
	std::mutex mLock;

#if EXCEPT_SAFETY_CODE
	// 자원 관리를 객체에 맡긴다.
	std::shared_ptr<Image> mBGImage;

#else
	// 픽셀 리소스 주소
	Image* mBGImage;

#endif // SOLVE_CODE

	// 이미지 변경횟수
	int ChangesCount = 0;

};

#if EXCEPT_SAFETY_CODE
// 예외 발생할 조건도 코드도 줄어듬
void PrettyMenu::ChangeBackGround(std::istream& _ImgSrc)
{
	// lock
	std::lock_guard<std::mutex> lock(mLock);

	// 자원 해제를 스마트 포인터에게 맡긴다.
	mBGImage.reset(new Image(read(_ImgSrc)));

	++ChangesCount;
}

#else
// 예외 발생 시, 문제가 될 수 있는 함수 예제
void PrettyMenu::ChangeBackGround(std::istream& _ImgSrc)
{
	// 뮤텍스 획득
	mLock.lock();

	// 이전 리소스를 삭제하고
	if (nullptr != mBGImage)
	{
		delete mBGImage;
		mBGImage = nullptr;
	}

	// 삭제 이후 예외 발생 시, 구조가 뒤틀어짐
	// 예외를 처리할 필요가 있음
	// 
	// 그리고 사용자가 new delete하는 것 보다
	// 스마트 포인터 객체에 자원을 맡기도록 하는게 좋다.

	++ChangesCount;

	// 입력으로부터 리소스 생성
	mBGImage = new Image(read(_ImgSrc));

	// 뮤텍스가 해제되기 전에 예외발생 시, 데드락 발생
	// 뮤텍스를 wrapper 클래스로 묶어 해결

	// 뮤텍스 해제
	mLock.unlock();
}

#endif // SOLVE_CODE

int main()
{

}