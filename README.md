Cinder is an API for the creation of dynamic c++ based visual elements. This is done in part via the intergration of many libraries such as cario, opengl, and many others. NOTE: Cario graphical objects are immediate mode, meaning they must be deleted tehn re-drawn in-order to any animations/moveemnts.

Our implementation of this API allows a user to create 2D graphics on top of the Cario/Cinder APIs so that an object created may rely on the data values of another. This method of binding an object to anothers/data value is called data constraints. The objects can support nested constraints, and these constraints are evaluated dynamically. This allows intricate events to be programmed into an object, achieving various results as a result. For Example: You have a circle that, upon adjustment, can re-size a constrained square.

This API, GraphicalObject, support the following operations
  1. Creation: The creation of an applicaion specific graphical object to a defined window
  2. Destruction/Deletion: The removal of an object from the current context with proper deletion methods
  3. Selection: The selection of an object via mouse events
  4. Moving: An overrideble function which allows users to specify the movments of an objects
  5. Rendering: A cario method which allows an object to be rendered to the users screen. This method uses standard cario syntax
  6. Bounding Box: A rectangle surounding an object. No rendered part of the object should appear outside this box. Events will not be handled out of the bounding box
  
DataConstraints support get (getting the constraints) and set (setting the constraints) methods. NOTE: setting the constraints forces the previous values of other dependent values to be marked as invalid, forcing their re-evaluation. The constraints themselves can be formulas, and templating the entire process may be acheved. For more information, view the data constraint example.
