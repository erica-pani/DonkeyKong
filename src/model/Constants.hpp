// define some constants to make code more readable
namespace constants {
    constexpr int VIEW_WIDTH = 600;
    constexpr int VIEW_HEIGHT = 600;
    constexpr unsigned int FRAME_RATE = 60;

    // barrel / girder physics (increment 2). Remember: the view is y-inverted,
    // so +y points downward (toward the bottom of the screen) = gravity direction.
    constexpr float BARREL_RADIUS = 12.f;     // px
    constexpr float ROLL_SPEED = 160.f;
    constexpr float MOVEMENT_SPEED = 140.f;      // px/sec, constant horizontal roll on a girder
    constexpr float GRAVITY = 900.f;          // px/sec^2, applied while falling
    constexpr float GIRDER_THICKNESS = 12.f;  // px
}
