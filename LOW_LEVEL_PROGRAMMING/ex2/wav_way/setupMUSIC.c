#include "game_types.h"
#include "music_used.h"

/* assign music/sounds to corresponding pins/state */

void setupMUSIC(sound_list* my_music)
{
	sound *def = &test; 

	my_music->intro 	= &star_wars_imperial;
	my_music->button[0] = &mario;
	my_music->button[1] = &star_wars_imperial;
	my_music->button[2] = &heavens_doors;
	my_music->button[3] = &hey_jude;
	my_music->button[4] = def; 
	my_music->button[5] = def;
	my_music->button[6] = def;
	my_music->button[7] = def;
}
