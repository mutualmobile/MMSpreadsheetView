// Copyright (c) 2013 Mutual Mobile (http://mutualmobile.com/)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <UIKit/UIKit.h>

@class MMSpreadsheetView;

/**
 An object that adopts the `MMSpreadsheetViewDataSource` protocol is responsible for providing the data and views required by a spreadsheet view. A data source object represents your app’s data model and vends information to the spreadsheet view as needed. It also handles the creation and configuration of cells used by the spreadsheet view to display your data.
 
 All data source objects must implement the `numberOfRowsInSpreadsheetView:`, `numberOfColumnsInSpreadsheetView:` and `spreadsheetView:cellForItemAtIndexPath:` methods. These methods are responsible for returning the number of items in the spreadsheet view along with the items themselves. In addition, the data source should implement the `spreadsheetView:sizeForItemAtIndexPath:` method for determining cell sizes in the individual collection views.

 When configuring the spreadsheet view object, assign your data source to its dataSource property. For more information about how a spreadsheet view works with its data source to present content, see `MMSpreadsheetView` Class Reference.
 @warning An NSIndexPath category is provided so that *indexPath.mmSpreadsheetRow* represents a row and *indexPath.mmSpreadsheetColumn* represents a column.
 */
@protocol MMSpreadsheetViewDataSource <NSObject>

@optional

///---------------------------------------
/// @name Spreadsheet Data Source Protocol
///---------------------------------------

/**
 The cell size for all cells in a collection view. Header cells can have a different size than non-header cells, but all cells within a single collection view (or spreadsheet view section) will be the same size.
 
 @param spreadsheetView The spreadsheet view object that is requesting the size information.
 @param indexPath The index path of the cell.
 
 @return A CGSize containing the height and width of the cell at the given indexPath.
 */
- (CGSize)spreadsheetView:(MMSpreadsheetView *)spreadsheetView sizeForItemAtIndexPath:(NSIndexPath *)indexPath;

@required

/**
 The number of horizontal rows for the entire `MMSpreadsheetView`.
 
 @param spreadsheetView The spreadsheet view object that is requesting the information.
 
 @return An NSInteger containing the number of horizontal rows in the spreadsheet view.
 */
- (NSInteger)numberOfRowsInSpreadsheetView:(MMSpreadsheetView *)spreadsheetView;

/**
 The number of vertical columns for the entire `MMSpreadsheetView`.
 
 @param spreadsheetView The spreadsheet view object that is requesting the information.
 
 @return An NSInteger containing the number of vertical columns in the spreadsheet view.
 */
- (NSInteger)numberOfColumnsInSpreadsheetView:(MMSpreadsheetView *)spreadsheetView;

/**
 Create and configure a cell for the `MMSpreadsheetView`.  The cell that is returned must be retrieved from a call to -`dequeueReusableCellWithReuseIdentifier:forIndexPath:`.

 @param spreadsheetView The spreadsheet view object that is requesting the cell.
 @param indexPath The index path of the cell.
 
 @return The dequeued `UICollectionViewCell` object.
 */
- (UICollectionViewCell *)spreadsheetView:(MMSpreadsheetView *)spreadsheetView cellForItemAtIndexPath:(NSIndexPath *)indexPath;

@end





/**
 
 The `MMSpreadsheetViewDelegate` protocol defines methods that allow you to manage the selection and highlighting of items in a spreadsheet view and to perform actions on those items. The methods of this protocol are all optional.
 
 When configuring the spreadsheet view object, assign your delegate object to its delegate property. For more information, see `MMSpreadsheetView` Class Reference.
 @warning An NSIndexPath category is provided so that *indexPath.mmSpreadsheetRow* represents a row and *indexPath.mmSpreadsheetColumn* represents a column.
 */
@protocol MMSpreadsheetViewDelegate <NSObject>
@optional
///---------------------------------------
/// @name Managing the Selected Cells
///---------------------------------------

/**
 Tells the delegate that the item at the specified index path was selected.
 
 @param spreadsheetView The spreadsheet view object that is notifying you of the selection change.
 @param indexPath The index path of the cell that was selected.
 */
- (void)spreadsheetView:(MMSpreadsheetView *)spreadsheetView didSelectItemAtIndexPath:(NSIndexPath *)indexPath;

///---------------------------------------
/// @name Managing Actions for Cells (Implement All or None)
///---------------------------------------

/**
 Asks the delegate if an action menu should be displayed for the specified item.
 
 @param spreadsheetView The spreadsheet view object that is making the request.
 @param indexPath The index path of the cell that was selected.
 
 @return YES if the editing menu should be shown positioned near the item and pointing to it, otherwise NO.
 @discussion If the user tap-holds a certain item in the spreadsheet view, this method (if implemented) is invoked first. Return YES if you want to permit the editing menu to be displayed. Return NO if the editing menu shouldn’t be shown—for example, you might return NO if the corresponding item contains data that should not be copied or pasted over.
 
 If you do not implement this method, the default return value is NO.
 
 **Note**: This is part of a set of three methods providing support for copy/paste actions on cells. All three should be implemented if any are.

 <p><strong>Availability</strong><br /></p><p>Available in iOS 6.0 and later.</p>
 
 @see spreadsheetView:canPerformAction:forItemAtIndexPath:withSender:
 
 spreadsheetView:performAction:forItemAtIndexPath:withSender:
 */
- (BOOL)spreadsheetView:(MMSpreadsheetView *)spreadsheetView shouldShowMenuForItemAtIndexPath:(NSIndexPath *)indexPath;

/**
 Asks the delegate if it can perform the specified action on an item in the collection view.
 
 @param spreadsheetView The spreadsheet view object that is making the request.
 @param action The selector identifying the action to be performed.
 @param indexPath The index path of the affected item.
 @param sender The object that wants to initiate the action.
 @return YES if the command corresponding to action should appear in the editing menu or NO if it should not.
 @discussion This method is invoked after the `spreadsheetView:shouldShowMenuForItemAtIndexPath:` method. It gives you the opportunity to exclude commands from the editing menu. For example, the user might have copied some content from one item and wants to paste it into another item that cannot accept the content. In such a case, your method could return NO to prevent the display of the relevant command.
 
 If you do not implement this method, the default return value is NO.

 **Note**: This is part of a set of three methods providing support for copy/paste actions on cells. All three should be implemented if any are.
 
 <p><strong>Availability</strong><br /></p><p>Available in iOS 6.0 and later.</p>
 
 @see spreadsheetView:performAction:forItemAtIndexPath:withSender:
 
 spreadsheetView:shouldShowMenuForItemAtIndexPath:
 */
- (BOOL)spreadsheetView:(MMSpreadsheetView *)spreadsheetView canPerformAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender;

/**
 Tells the delegate to perform the specified action on an item in the spreadsheet view.
 
 @param spreadsheetView The spreadsheet view object that is making the request.
 @param action The selector representing the action to be performed.
 @param indexPath The index path of the affected item.
 @param sender The object that initiated the action.
 @discussion If the user taps an action in the editing menu, the spreadsheet view calls this method. Your implementation of this method should do whatever is appropriate for the action. For example, for a copy action, it should extract the relevant item content and write it to the general pasteboard or an application (private) pasteboard.
 
 For information about how to perform pasteboard-related operations, see `UIPasteboard` Class Reference.

 **Note**: This is part of a set of three methods providing support for copy/paste actions on cells. All three should be implemented if any are.
 
 <p><strong>Availability</strong><br /></p><p>Available in iOS 6.0 and later.</p>
 
 @see spreadsheetView:shouldShowMenuForItemAtIndexPath:
 
 spreadsheetView:canPerformAction:forItemAtIndexPath:withSender:
 */
- (void)spreadsheetView:(MMSpreadsheetView *)spreadsheetView performAction:(SEL)action forItemAtIndexPath:(NSIndexPath *)indexPath withSender:(id)sender;

@end







/**
 `MMSpreadsheetView` is a configurable spreadsheet-like view. You choose to configure the view with zero or more header rows and zero or more header columns. Depending on this configuration, up to four collection views will be coordinated to provide the user interface. 
 

 When adding a spreadsheet view to your user interface, your app’s main job is to manage the data associated with the view. The spreadsheet view gets its data from the data source object, which is an object that conforms to the `MMSpreadsheetViewDataSource` protocol and is provided by your app. The spreadsheet view presents items onscreen using a cell, which is an instance of the UICollectionViewCell class that your data source configures and provides.
 
 ## Creating an MMSpreadsheetView
 `MMSpreadsheetView` is similar to a `UICollectionView` or `UITableView`. To create an `MMSpreadsheetView`, you instantiate the view using initWithNumberOfHeaderRows:numberOfHeaderColumns:frame:.
 
 @discussion **Note**: Set the background color of the spreadsheet view to change the separator line color. **However**, you will also see this color when the scroll goes into a bounce.
 
 @warning An NSIndexPath category is provided so that *indexPath.mmSpreadsheetRow* represents a row and *indexPath.mmSpreadsheetColumn* represents a column.
 @warning as the number of cells shown increases, scrolling performance declines. A large grid (1000x1000) takes a long time to initialize, but if the cell sizes are large enough (150x150), scrolling performance is not affected. However, a small grid (50x50) of (20x20) cells basically doesn't scroll.
 */
@interface MMSpreadsheetView : UIView

///---------------------------------------
/// @name Spreadsheet View Properties
///---------------------------------------

/**
 The object that acts as the delegate of the spreadsheet view.
 
 @discussion The delegate must adopt the `MMSpreadsheetViewDelegate` protocol. The spreadsheet view maintains a weak reference to the delegate object.
 
 The delegate object is responsible for managing selection behavior and interactions with individual items.
 */
@property (nonatomic, weak) id<MMSpreadsheetViewDelegate> delegate;

/**
 The object that provides the data for the spreadsheet view.
 
 @discussion The data source must adopt the `MMSpreadsheetViewDataSource` protocol. The spreadsheet view maintains a weak reference to the data source object.
 */
@property (nonatomic, weak) id<MMSpreadsheetViewDataSource> dataSource;


///---------------------------------------
/// @name Initializing & Setup
///---------------------------------------

/**
 Initializes and returns a spreadsheet view object given the number of header rows, columns and bounds. This method is the *designated initializer*.
 
 @param headerRowCount The number of header **rows** at the top of the view.
 @param headerColumnCount The number of header **columns** on the left side of the view.
 @param frame The frame rectangle for the spreadsheet view, measured in points. The origin of the frame is relative to the superview in which you plan to add it. This frame is passed to the superclass during initialization.
 
 @return An initialized spreadsheet view object or nil if the object could not be created.
 
 */
- (id)initWithNumberOfHeaderRows:(NSUInteger)headerRowCount numberOfHeaderColumns:(NSUInteger)headerColumnCount frame:(CGRect)frame;

/**
 Register a class for use in creating new spreadsheet view cells.
 
 @param cellClass The class of a cell that you want to use in the spreadsheet view.
 @param identifier The reuse identifier to associate with the specified class. This parameter must not be nil and must not be an empty string.
 @discussion Prior to calling the dequeueReusableCellWithReuseIdentifier:forIndexPath: method of the spreadsheet view, you must use this method to tell the spreadsheet view how to create a new cell of the given type. If a cell of the specified type is not currently in a reuse queue, the spreadsheet view uses the provided information to create a new cell object automatically.
 
 If you previously registered a class with the same reuse identifier, the class you specify in the cellClass parameter replaces the old entry. You may specify nil for cellClass if you want to unregister the class from the specified reuse identifier.
 
 */
- (void)registerCellClass:(Class)cellClass forCellWithReuseIdentifier:(NSString *)identifier;

///---------------------------------------
/// @name Creating Spreadsheet View Cells
///---------------------------------------

/**
 Returns a reusable cell object located by its identifier.
 
 @param identifier The reuse identifier for the specified cell. This parameter must not be nil.
 @param  indexPath The index path specifying the location of the cell. The data source receives this information when it is asked for the cell and should just pass it along. This method uses the index path to perform additional configuration based on the cell’s position in the spreadsheet view.

 @return A valid `UICollectionViewCell` object.

 @discussion Call this method from your data source object when asked to provide a new cell for the spreadsheet view. This method dequeues an existing cell if one is available or creates a new one based on the class you previously registered.
 
 @warning You must register a class using the `registerCellClass:forCellWithReuseIdentifier:` method before calling this method.
 
 @discussion If you registered a class for the specified identifier and a new cell must be created, this method initializes the cell by calling its initWithFrame: method. If an existing cell was available for reuse, this method calls the cell’s prepareForReuse method instead.
 */
- (UICollectionViewCell *)dequeueReusableCellWithReuseIdentifier:(NSString *)identifier forIndexPath:(NSIndexPath *)indexPath;

///---------------------------------------
/// @name Managing the Selection
///---------------------------------------

/**
 Deselects the item at the specified index.
 
 @param indexPath The index path of the item to deselect. Specifying `nil` for this parameter removes the current selection.
 @param animated Specify YES to animate the change in the selection or NO to make the change without animation.
 @discussion If the allowsSelection property is NO, calling this method has no effect.
 
 This method does not cause any selection-related delegate methods to be called.
 
 */
- (void)deselectItemAtIndexPath:(NSIndexPath *)indexPath animated:(BOOL)animated;

///---------------------------------------
/// @name Reloading Content
///---------------------------------------

/**
 Reloads all of the data for the spreadsheet view.
 
 @discussion Call this method to reload all of the items in the spreadsheet view. This causes the spreadsheet view to discard any currently visible items and redisplay them. For efficiency, the spreadsheet view only displays those cells that are visible. If the spreadsheet data shrinks as a result of the reload, the spreadsheet view adjusts its scrolling offsets accordingly.
 
 */
- (void)reloadData;

///---------------------------------------
/// @name Managing the Scroll Indicator
///---------------------------------------

/**
 The distance the scroll indicators are inset from the edge of the scroll view.
 
 @discussion The default value is UIEdgeInsetsZero.
 */
@property (nonatomic, assign) UIEdgeInsets scrollIndicatorInsets;

/**
 A Boolean value that controls whether the horizontal scroll indicator is visible.
 
 @discussion The default value is YES. The indicator is visible while tracking is underway and fades out after tracking.
 */
@property (nonatomic, assign) BOOL showsHorizontalScrollIndicator;

/**
 A Boolean value that controls whether the vertical scroll indicator is visible.
 
 @discussion The default value is YES. The indicator is visible while tracking is underway and fades out after tracking.
 */
@property (nonatomic, assign) BOOL showsVerticalScrollIndicator;

/**
 Displays the scroll indicators momentarily.
 
 @discussion You should call this method whenever you bring the scroll view to front.
 */
- (void)flashScrollIndicators;

///---------------------------------------
/// @name Scroll View Properties
///---------------------------------------

/**
 A Boolean value that controls whether the spreadsheet view bounces past the edge of content and back again.
 
 @discussion If the value of this property is YES, the spreadsheet view bounces when it encounters a boundary of the content. Bouncing visually indicates that scrolling has reached an edge of the content. If the value is NO, scrolling stops immediately at the content boundary without bouncing. The default value is YES.
 */
@property (nonatomic, assign) BOOL bounces;

@end
