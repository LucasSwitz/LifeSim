#include "src/game_objects/actor/Actor.h"

class Starved : public Condition<Actor>
{
    void virtual Start(Actor& actor) override;
    void virtual Update(Actor& actor) override;
    void virtual End(Actor& actor) override;
    bool virtual isFinished(Actor& actor) override;
}