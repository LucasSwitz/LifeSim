#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/goal/Nutrition.h"
#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/actions/ActionChain.h"
#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/actions/ActionEat.h"

    class Statics
    {
    public:
        static void Init()
        {     
	 Nutrition::Instance(); 
	 new ActionChain(); 
	 new ActionEat(); 
} 
 };