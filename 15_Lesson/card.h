#pragma once

/*
Club    = Sinek
Diamond = Karo
Heart   = Kupa
Spade   = Ma�a
*/

#ifdef POKER
	typedef enum { Club, Diamond, Heart, Spade}Suit;
#else
	typedef enum { Club, Diamond, Spade, Heart}Suit;
#endif

