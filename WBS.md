## Image downloader application ##

1. Plannig              _34 h._        
    1. Requirements analysis               _20 h._
    2. Documentation prep                  _14 h._
        1. WBS                             _3 h._
        2. UML class-diagram               _3 h._
        3. Application modules descriptoin _4 h._
        5. Sequence diagram                _4 h._
2. Developing           _140 h._                     
    1. Main functionlity                   _80 h._
        1. User setings                                        _16 h._
            1. Directory for dwonloads                                              _5 h._
            2. Image format (jpg, bmp, png, ...)                                    _5 h._
            3. Maximum image count (deafult 10 images)                              _6 h._
        2. Serching images over Internet                       _24 h._ 
            1. Serch request                                                        _10 h._
            2. Result handler                                                       _14 h._
                1. Saving list of links                                                                 _5 h._
                2. Saving original title and extension for each image                                   _5 h._
        3. Downloading                                         _30 h._
            1. Downloding images to the selected directory.                         _8 h._ 
            2. If User didn`t select directory uses default directory:              _2 h._
                                    C:\Users\User_Name\Downloads\ for Windows,
                                    home/User_Name/downloads/ for Linux)
            3. Convert picture to the selected extension                            _4 h._
            4. If exteansion didn`t selected save image in original foramt          _1 h._
            5. Downloading multiple images                                          _15 h._
                1. Parallel downloading                                                                 _9 h._
                2. Asynchronous downloading (not blocking UI)                                           _7 h._
        4. History of search requests                           _10 h._
    2. GUI                                 _60 h._
        1. Main desktop                                         _40 h._
            1. Input line                                                           _10 h._
                1. Line for keywords of serach request                                                  _6 h._
                2. "Search" button                                                                      _4 h._
            2. Result area                                                          _30 h._
                1. Visualization setting                                                                _16 h._
                    1. List of images (title, size, format)                                                                 _8 h._
                    2. Table of images (images thumbnails, title in bottom of image)                                        _8 h._
                2. Mouse seting                                                                         _6 h._
                    1. One click: choose image of download                                                                  _3 h._
                    2. Double click: open original image in new window                                                      _3 h._
                3. "Download" and "Cancel" buttons                                                      _4 h._
                4. Progress bar for each downloded image                                                _4 h._
        2. User toolbar                                         _20 h._
            1. Setings                                                              _6 h._
                1. Download directory                                                                   _2 h._
                2. Image foramt                                                                         _2 h._
                3. Maximum image count                                                                  _2 h._
            2. History                                                              _12 h._
                1. Period (last hour, day, week, ...)                                                   _6 h._
                2. Area of result                                                                       _6 h._
            3. Info (windows with information about application)                    _2 h._
3. Testing              _6 h._
    1. Windows testing                      _3 h._
    2. Linux testing                        _3 h._
4. Deployment           _6 h._
    1. Requirements specification           _2 h._
    2. Readme file                          _2 h._
    4. Merge request                        _1 h._