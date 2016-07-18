typedef struct Vector2D
{
	double x;
	double y;
} Vector2D;

typedef struct Rect
{
	Vector2D downleft;
	Vector2D upright;
} Rect;

void bounceCharacter( Vector2D * speed, Vector2D * position	);
void renderPlayers	( Vector2D p1_pos, Vector2D p2_pos		);
void joyAtkHandler	( u16 joy, u16 joyChanged, u16 state	);
double dot 			( Vector2D v1, Vector2D v2 );
Vector2D diff		( Vector2D v1, Vector2D v2 );
double sqDist		( Vector2D v1, Vector2D v2 );

const static Vector2D V2D_NORTH = {  0,  1 };
const static Vector2D V2D_SOUTH = {  0, -1 };
const static Vector2D  V2D_EAST = {  1,  0 };
const static Vector2D  V2D_WEST = { -1,  0 };

// const static enum {
// 	NORTH,
// 	SOUTH,
// 	EAST,
// 	WEST
// };