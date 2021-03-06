/*
 * cocos2d for iPhone: http://www.cocos2d-iphone.org
 *
 * Copyright (c) 2008-2010 Ricardo Quesada
 * Copyright (c) 2011 Zynga Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */



#import "ccMacros.h"

#ifdef __CC_PLATFORM_IOS
#import <UIKit/UIKit.h>									// Needed for UIAccelerometerDelegate
#elif defined(__CC_PLATFORM_MAC)

#endif

#import "CCProtocols.h"
#import "CCNode.h"

#pragma mark -
#pragma mark CCNodeColor

/**
 *  CCNodeColor is a subclass of CCNode that implements the CCRGBAProtocol protocol.
 *
 *  All features from CCNode are valid, plus the following new features:
 *  - opacity
 *  - RGB colors
 */
@interface CCNodeColor : CCNodeRGBA <CCBlendProtocol>
{
	ccVertex2F	_squareVertices[4];
	ccColor4F	_squareColors[4];

	ccBlendFunc	_blendFunc;
}

/**
 *  Creates a CCNode with color, width and height in Points.
 *
 *  @param color Color of the node.
 *  @param w     Width of the node.
 *  @param h     Height of the node.
 *
 *  @return New CCNodeColor
 */
+ (id) nodeWithColor: (ccColor4B)color width:(GLfloat)w height:(GLfloat)h;

/**
 *  Creates a CCNode with color. Width and height are the window size.
 *
 *  @param color Color of the node.
 *
 *  @return New CCNodeColor
 */
+ (id) nodeWithColor: (ccColor4B)color;

/**
 *  Initializes a CCNode with color, width and height in Points.
 *
 *  @param color Color of the node.
 *  @param w     Width of the node.
 *  @param h     Height of the node.
 *
 *  @return New CCNodeColor
 */
- (id) initWithColor:(ccColor4B)color width:(GLfloat)w height:(GLfloat)h;

/**
 *  Inirializes a CCNode with color. Width and height are the window size.
 *
 *  @param color Color of the node.
 *
 *  @return New CCNodeColor
 */
- (id) initWithColor:(ccColor4B)color;

/** BlendFunction. Conforms to CCBlendProtocol protocol */
@property (nonatomic,readwrite) ccBlendFunc blendFunc;
@end

#pragma mark -
#pragma mark CCNodeGradient

/** 
 *  CCNodeGradient is a subclass of CCNodeColor that draws gradients across the background.
 *
 *  All features from CCNodeColor are valid, plus the following new features:
 *  - direction
 *  - final color
 *  - interpolation mode
 *
 *  Color is interpolated between the startColor and endColor along the given vector (starting at the origin, ending at the terminus).  
 *
 *  If no vector is supplied, it defaults to (0, -1) -- a fade from top to bottom.
 *
 *  If 'compressedInterpolation' is disabled, you will not see either the start or end color for non-cardinal vectors; a smooth gradient implying both end points will be still be drawn, however.
 *
 *  If ' compressedInterpolation' is enabled (default mode) you will see both the start and end colors of the gradient.
 */
@interface CCNodeGradient : CCNodeColor
{
	ccColor3B _endColor;
	GLubyte _startOpacity;
	GLubyte _endOpacity;
	CGPoint _vector;
	BOOL	_compressedInterpolation;
}

/* Creates a full-screen CCNode with a gradient between start and end. */
+ (id) nodeWithColor: (ccColor4B) start fadingTo: (ccColor4B) end;
/* Creates a full-screen CCNode with a gradient between start and end in the direction of v. */
+ (id) nodeWithColor: (ccColor4B) start fadingTo: (ccColor4B) end alongVector: (CGPoint) v;

/* Initializes the CCNode with a gradient between start and end. */
- (id) initWithColor: (ccColor4B) start fadingTo: (ccColor4B) end;
/* Initializes the CCNode with a gradient between start and end in the direction of v. */
- (id) initWithColor: (ccColor4B) start fadingTo: (ccColor4B) end alongVector: (CGPoint) v;

/** The starting color. */
@property (nonatomic, readwrite) ccColor3B startColor;
/** The ending color. */
@property (nonatomic, readwrite) ccColor3B endColor;
/** The starting opacity. */
@property (nonatomic, readwrite) GLubyte startOpacity;
/** The ending color. */
@property (nonatomic, readwrite) GLubyte endOpacity;
/** The vector along which to fade color. */
@property (nonatomic, readwrite) CGPoint vector;
/** Whether or not the interpolation will be compressed in order to display all the colors of the gradient both in canonical and non canonical vectors.
 *
 *  Default: YES
 */
@property (nonatomic, readwrite) BOOL compressedInterpolation;

@end

#pragma mark -
#pragma mark CCNodeMultiplexer

/** CCNodeMultiplexer is a CCNode with the ability to multiplex its children.
 *
 *  Features:
 *
 *  - It supports one or more children
 *  - Only one children will be active a time
 */
@interface CCNodeMultiplexer : CCNode
{
	unsigned int _enabledNode;
	NSMutableArray *_nodes;
}

// ----------------------------------------------------------
/** @name Factory methods */
// ----------------------------------------------------------
/**
 *  Creates a CCNodeMultiplexer with an array of layers.
 *
 *  @param arrayOfNodes Array of nodes.
 *
 *  @return New CCNodeMultiplexer
 */
+(id) nodeWithArray:(NSArray*)arrayOfNodes;

/** Creates a CCMultiplexLayer with one or more layers using a variable argument list.

Example:

    mux = [CCNodeMultiplexer nodeWithNodes:nodeA, nodeB, nodeC, nil];

@param node List of nodes.
@param ... nil terminated list of nodes.
@return New CCNodeMultiplexer
 */
+(id) nodeWithNodes: (CCNode*) node, ... NS_REQUIRES_NIL_TERMINATION;

// ----------------------------------------------------------
/** @name Initializers */
// ----------------------------------------------------------
/**
 *  Initializes a CCNodeMultiplexer with an array of layers.
 *
 *  @param arrayOfNodes Array of nodes.
 *
 *  @return New CCNodeMultiplexer
 */

-(id) initWithArray:(NSArray*)arrayOfNodes;

// ----------------------------------------------------------
/** @name Node activation */
// ----------------------------------------------------------
/**
 *  Switches to a certain node indexed by n.
 *
 *  The current (old) node will be removed from its parent with 'cleanup:YES'.
 *
 *  @param n Index of node to switch to
 */
-(void) switchTo: (unsigned int) n;

@end

