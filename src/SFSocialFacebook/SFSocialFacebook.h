//
//  SFSocialFacebook.h
//  SFSocialFacebook
//
//  Created by Massaki on 11/1/11.
//  Copyright (c) 2011 I.ndigo. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "FBConnect.h"
#import "SFSimplePost.h"
#import "SFSimpleUser.h"
#import "SFEvent.h"
#import "SFFacebookRequest.h"

typedef void (^SFFailureBlock)(NSError *error);
typedef void (^SFBasicBlock)(void);
typedef void (^SFDidNotLoginBlock)(BOOL cancelled);
typedef void (^SFListObjectsBlock)(NSArray *objects, NSString *nextPageUrl);
typedef void (^SFCreateObjectBlock)(NSString *objectId);

typedef enum {
    SFDialogRequestPublish,  
} SFDialogRequest;

@protocol SFPostDatasource;

@class SFURLRequest;

@interface SFSocialFacebook : NSObject <FBSessionDelegate, FBDialogDelegate, UIAlertViewDelegate> {
    
    Facebook            *_facebook;
    NSArray             *_permissions;
    NSString            *_appId;
    NSString            *_appSecret;
    NSString            *_appAccessToken;
    
    SFURLRequest        *_urlRequest;
    
    SFBasicBlock        _loginBlock;
    SFDidNotLoginBlock  _notLoginBlock;
    SFBasicBlock        _logoutBlock;
    
    SFDialogRequest     _currentDialogRequest;
    id                  _dialogSuccessBlock;
    SFFailureBlock      _dialogFailureBlock;
    SFBasicBlock        _dialogCancelBlock;
    
    NSDateFormatter     *_dateFormatter;
    NSTimeZone          *_facebookTimeZone;
    NSTimeZone          *_localTimeZone;
    
	NSString *facebookUserId;
    int areaId;
	
    NSString *shingleServerPath;
	
	SEL pendingAction;
	NSMutableDictionary *pendingActionParams;
}

+ (SFSocialFacebook *)sharedInstance;
+ (SFSocialFacebook *)sharedInstanceWithAppId:(NSString *)appId appSecret:(NSString *)appSecret urlSchemeSuffix:(NSString *)urlSchemeSuffix andPermissions:(NSArray *)permissions;


@property (nonatomic, retain) NSString *facebookUserId;
@property (nonatomic, retain) NSString *loggedUserId;

- (BOOL)handleOpenURL:(NSURL *)url;
- (BOOL)isSessionValid:(BOOL)needsLogin;

- (void)getAppAccessTokenWithSuccess:(void (^)(NSString *accessToken))successBlock failure:(SFFailureBlock)failureBlock;

- (void)loginWithSuccess:(SFBasicBlock)successBlock failure:(SFDidNotLoginBlock)failureBlock;
- (void)logoutWithSuccess:(SFBasicBlock)successsBlock;
- (SFFacebookRequest *)uninstallApp:(SFBasicBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (SFFacebookRequest *)profileFeed:(NSString *)profileId pageSize:(NSUInteger)pageSize needsLogin:(BOOL)needsLogin success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)profileFeedNextPage:(NSString *)nextPageUrl success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (void)publishPost:(SFSimplePost *)post success:(SFCreateObjectBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (SFFacebookRequest *)listFriendsWithPageSize:(NSUInteger)pageSize success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)listFriendsNextPage:(NSString *)nextPageUrl success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

/** requires user_events permission **/
- (SFFacebookRequest *)listEventsWithPageSize:(NSUInteger)pageSize success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)listEventsNextPage:(NSString *)nextPageUrl success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

/** requires create_event permission **/
- (SFFacebookRequest *)createEvent:(SFEvent *)event success:(SFCreateObjectBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)inviteUsers:(NSArray *)userIds toEvent:(NSString *)eventId success:(SFBasicBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

/** requires user_events permission **/
- (SFFacebookRequest *)invitedUsersForEvent:(NSString *)eventId pageSize:(NSUInteger)pageSize success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)invitedUsersForEvent:(NSString *)eventId rsvpStatus:(SFUserRSVPStatus)rsvpStatus pageSize:(NSUInteger)pageSize success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;
- (SFFacebookRequest *)invitedUsersNextPage:(NSString *)nextPageUrl success:(SFListObjectsBlock)successBlock failure:(SFFailureBlock)failureBlock cancel:(SFBasicBlock)cancelBlock;

- (void) handleLike: (NSString *) postId;
//- (void) handleComment: (NSString *) comment InPost: (NSString *) postId;
//- (void) handleUnlike: (NSString *) postId;

- (void) getEvent: (NSString*) eventId;
- (void) eventMarkAttending: (NSString *)eventId;
- (void) getNumLikesFromPage: (NSString *)pageId;
- (void) getAccessTokenWithClientId:(NSString*)client_id andClientSecret:(NSString*)client_secret;

@end
