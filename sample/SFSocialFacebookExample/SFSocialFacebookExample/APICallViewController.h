//
//  APICallViewController.h
//  SFSocialFacebookExample
//
//  Created by Massaki on 1/5/12.
//  Copyright (c) 2012 I.ndigo. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface APICallViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
    UITableView *_tableView;
    NSArray *_menuOptions;
    NSString *_eventId;
}

- (id)initWithMenu:(NSString *)menu;
- (id)initWithEventId:(NSString *)eventId;

@end
