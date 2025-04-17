#pragma once
#include <string>

// 설명: 텍스트 기반 렌더링을 담당한다.
class GameEngineText
{
public:
	/**
	* @brief								Write Message to buffer
	*
	* @param const std::string& _Text		This parameter is rendering Message
	*
	* @return int							If the function encounters a problem, 
	*												it returns failed.
	*/
	int Write(const std::string& _Text);

	/// <summary>
	/// 
	/// </summary>
	/// <returns></returns>
	const std::string& Get();

private:
	/* Render Text */
	void Render();

private:
	std::string Buffer; // Message를 보관할 데이터 멤버

};