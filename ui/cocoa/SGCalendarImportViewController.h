//
// Created by Dmitry Khrykin on 03/05/2020.
//

#ifndef STRATEGR_SGCALENDARIMPORTVIEWCONTROLLER_H
#define STRATEGR_SGCALENDARIMPORTVIEWCONTROLLER_H

#import <AppKit/AppKit.h>
#import "SGCalendarImportExportView.h"

@interface SGCalendarImportViewController : NSViewController <NSWindowDelegate, SGCalendarImportExportViewDelegate>
- (void)optionsViewWantsCancel;
- (void)optionsViewWantsPerform;
@end

#endif //STRATEGR_SGCALENDARIMPORTVIEWCONTROLLER_H
