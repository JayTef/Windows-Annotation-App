Draw smooth lines
1. Mouse Down -> Start
2. Mouse Move -> Add dots
3. Mouse Up -> Finish
4. Draw line that connect dots -> CDC::MoveTo, CDC::LineTo
5. use variable isDown
----------------------------------------------------------------



flashes, Invalidate
1. read the manual
2. FALSE
----------------------------------------------------------------



Separate each line, use another vector
1. down -> move -> up.
2. store each line in lines
3. show each line
----------------------------------------------------------------



Create colour object, pointer (copy its address)
1. copying object costs many memory (deep copy)
2. pointer assign address of object (shallow copy)
3. create CLine file
----------------------------------------------------------------



Create Rectangle & Ellipse
   - Rectangle -> CDC::Rectangle -> LBU -> store in vector
   - Ellipse -> CDC::Ellipse
1. Connect the only first and seconed array so that it can save unnecessary array while moving mouse.
   - memory, valiable, &, *
----------------------------------------------------------------



Create CShapes class
1. find similarities and differences -> generalisation 
2. abstraction so that other programmers cannot access properties 
----------------------------------------------------------------



Import DLL
1. CreateCompatibleDC method
2. Gdiplus library
----------------------------------------------------------------



Add more Shapes 
   - Right Triangle -> Polygon p1, p2, p3
   - Triangle -> (pt1.X + pt2.X) / 2, pt1.Y) = p1 in the middle
   - Straight Line -> g.DrawPolygon(&m_pen, points.data(), points.size()); OR g.DrawLine(&m_pen, pt1, pt2);
   - Arrow -> Gdiplus::AdjustableArrowCap myArrow(5, 5, true);
----------------------------------------------------------------





============================================================================================================





Add more Features 1
   - transparent window -> replace copyTo with UpdateSurface     
   - Text Input -> CEdit & Ctext Class                                *<---
        1. size of rect  
             - CMyEdit
             - GDI+ MeasureString
             - Tab -> CString::Replace
             - blinking text cursor ->
        2. text transparent 
             - UpdateSurface 
             - CTextInputBox -> CEdit
             - OnCreate
        3. reset text  -> 
----------------------------------------------------------------



Add more Features 2
   - Fill shapes ->                                             
   - Eraser -> Delete Object itself                                
   - Undo & Redo-> Lambda to remember functions 
----------------------------------------------------------------



Add more Features 3
   - Rotation ->    
   - Copy&Paste ->
   - import images ->    
----------------------------------------------------------------



Design
   - menu bar ->   
   - Launch ->
----------------------------------------------------------------






============================================================================================================
(open source project on github)
   - Other type of pens (Calligraphy, Brush, Creyon, Spray, *mirror brush) 
   - Eraser -> Clip
   - spline
   - Mac ver
============================================================================================================