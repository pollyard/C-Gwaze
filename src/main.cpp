#include "Pick.h"

int main(int argc, char* argv[])
{
	Pick pick;
	srand(time(NULL));

	bool success = pick.Init();
	if (success) {
		pick.Loop();
	}

	pick.~Pick();
	return 0;
}