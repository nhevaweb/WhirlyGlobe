//
//  MapyTestCase.h
//  AutoTester
//
//  Created by jmnavarro on 13/10/15.
//  Copyright © 2015 mousebird consulting. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "MaplyTestResult.h"


@class MaplyViewController;
@class WhirlyGlobeViewController;
@class MaplyTestCase;
@class MaplyCoordinateSystem;

typedef void (^TestCaseResult)(MaplyTestCase * _Nonnull testCase);

typedef NS_OPTIONS(NSUInteger, MaplyTestCaseOptions) {
	MaplyTestCaseOptionGlobe = 1 << 1,
	MaplyTestCaseOptionMap   = 1 << 2,
};

typedef NS_OPTIONS(NSUInteger, MaplyTestCaseState) {
	MaplyTestCaseStateDownloading,
	MaplyTestCaseStateReady,
	MaplyTestCaseStateSelected,
	MaplyTestCaseStateError,
	MaplyTestCaseStateRunning,
};

@interface MaplyTestCase : NSObject

- (void)start;

// these prototypes are necessary for Swift
- (BOOL)setUpWithGlobe:(WhirlyGlobeViewController * _Nonnull)globeVC;
- (void)tearDownWithGlobe:(WhirlyGlobeViewController * _Nonnull)globeVC;
- (NSArray * _Nullable)remoteResources;

- (BOOL)setUpWithMap:(MaplyViewController * _Nonnull)mapVC;
- (void)tearDownWithMap:(MaplyViewController * _Nonnull)mapVC;

- (MaplyCoordinateSystem * _Nullable)customCoordSystem;

@property (nonatomic, strong) UIView * _Nullable testView;
@property (nonatomic, strong) NSString * _Nonnull name;
@property (nonatomic, copy) TestCaseResult _Nullable resultBlock;
@property (nonatomic) NSInteger captureDelay;

@property (nonatomic) MaplyTestCaseOptions options;

@property (nonatomic) MaplyTestCaseState state;
@property (nonatomic) BOOL interactive;

@property (nonatomic) NSInteger pendingDownload;

@property (nonatomic, copy, nullable) void (^updateProgress)(BOOL enableIndicator);


@property (nonatomic, strong) WhirlyGlobeViewController *_Nullable globeViewController;
@property (nonatomic, strong) MaplyViewController * _Nullable mapViewController;

@property (nonatomic, readonly) MaplyTestResult * _Nullable globeResult;
@property (nonatomic, readonly) MaplyTestResult * _Nullable mapResult;

@end
