/*
	Copyright 2021 Andrew Morse
	apache 2.0 license
	
	Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
			http://www.apache.org/licenses/LICENSE-2.0
			
	this is distributed under the License, which is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
	
	this source code for this software is available on github, https://github.com/RockyRoad000/particeTest/
	I have used this in other github repositories, some of which are not distributed under the apache license, THIS PARTICLE LIBRARY STILL IS, you can obtain it from the previous github download link
*/

// this software uses SFML for graphics, which is available at https://www.sfml-dev.org/download.php
// I did not write SFML, and I am not tring to take credit for it, a license for SFML is available at https://www.sfml-dev.org/license.php#extlibs, it is distributed under the zlib/png license

#include <vector>
#include <stdlib.h> // srand, rand
#include <stdio.h> // NULL
#include <time.h> // time
#include <math.h> // sin and cos
class ParticleSystem
{
	private:
		std::vector<std::vector<float>> particles;
	public:
		void createParticleSystem(float startX, float startY, long int startAmount, int startSpread, float spreadSpeedMin, float spreadSpeedMax)
		{
			srand (time(NULL));
			for(int i = 0; i < startAmount; i++)
			{
				// finds the spreadspeed, a random number between then max and the minimum, it multiplies by 1000 then divides by 1000 because c++ rand() doesn't accept anything besides integers
				float spreadSpeed = static_cast<float>(((rand() % (static_cast<int>(spreadSpeedMax*1000) - static_cast<int>(spreadSpeedMin*1000))) + spreadSpeedMin*1000)/1000);
				std::vector<float> temp = {startX + (rand() % startSpread)-startSpread/2, startY + (rand() % startSpread)-startSpread/2, spreadSpeed, static_cast<float>(rand() % 360), -1, 0};
				// the rand % 360 on the last line finds a random angle, in degrees that it will spread out with. The last two are used later, for how much it has faded and the rate at which it will fade repectively
				particles.push_back(temp);
			}
		}
		void updateParticleSystem()
		{
			for(int i = 0; i < particles.size(); i++)
			{
				float spreadSpeed = particles[i][2];
				float translation[] = {spreadSpeed * cos(particles[i][3]), spreadSpeed * sin(particles[i][3])};
				particles[i][0] += translation[0];
				particles[i][1] += translation[1];
			}
		}
		bool drawParticleSystem(float size, int shapeSides, int r, int g, int b, int o, float fadeSpeedMin, float fadeSpeedMax)
		{
			bool stillCanDraw = false;
			sf::CircleShape triangle(size, shapeSides);
			for(int i = 0; i < particles.size(); i++)
			{
				if(particles[i][4] > 0 || particles[i][4] == -1) // detects if it has faded all the way out yet
				{
					if(particles[i][5] == 0)
					{
						particles[i][4] = o;
						particles[i][5] = static_cast<float>(((rand() % (static_cast<int>(fadeSpeedMax*1000) - static_cast<int>(fadeSpeedMin*1000))) + fadeSpeedMin*1000)/1000);
					}
					triangle.setPosition(particles[i][0], particles[i][1]);
					triangle.setFillColor(sf::Color(r, g, b, o+particles[i][4]));
					window.draw(triangle);
					particles[i][4]-=particles[i][5];
					stillCanDraw = true;
				}
			}
			return stillCanDraw;
		}

};