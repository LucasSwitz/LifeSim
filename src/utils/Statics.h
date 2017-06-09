#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/goal/Nutrition.h"
#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/actions/ActionScriptChain.h"
#include "/home/lucas/Desktop/LifeSim/src/game_objects/actor/actions/ActionEat.h"

    class Statics
    {
    public:
        static void Init()
        {     
	 Nutrition::Instance(); 
	 new ActionScriptChain(); 
	 new ActionEat(); 
} 
 };