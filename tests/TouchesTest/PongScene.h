/* TouchesTest (c) Valentin Milea 2009
 */
#import "cocos2d.h"

@interface PongScene : CCScene {
@private
}
@end

@class Ball;

@interface PongLayer: CCNode {
@private
	Ball *ball;
	NSArray *paddles;
	CGPoint ballStartingVelocity;
}
@end
