#include "GameManager.h"
#include "QuitButton.h"

QuitButton::QuitButton()
{
	setViewString("Quit"); 
	setLocation(df::BOTTOM_RIGHT);
}

void QuitButton::callback()
{
	GM.setGameOver();
}
