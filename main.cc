#include "GameHandler.h"
#include "system.h"
#include "thread.h"

__USING_API

int main(void)
{
   System::init(&GameHandler::run);
}