#ifndef __TRACKLETWINDOWS_H__
#define __TRACKLETWINDOWS_H__

namespace TMTT{

 class TrackletWindows{

  public:

   TrackletWindows() :

    phiMatchingWindowsBarrel //first index (row) is layer number, second index (column) is tracklet seed type
     //zero elements are unused
    {
      { 0,    0.07, 0.08, 0.07, 0.05, 0,    0.05, 0.10 },//layer 1 phi windows
      { 0,    0.06, 0.08, 0.05, 0,    0,    0,    0    },//layer 2 phi windows
      { 0.10, 0,    0.08, 0,    0,    0,    0,    0    },//layer 3 phi windows
      { 0.19, 0,    0.05, 0,    0,    0,    0,    0.19 },//layer 4 phi windows
      { 0.4,  0.08, 0,    0,    0,    0,    0,    0.4  },//layer 5 phi windows
      { 0.5,  0.19 ,0,    0,    0,    0,    0,    0    } //layer 6 phi windows
    },
    zMatchingWindowsBarrel //first index (row) is layer number, second index (column) is tracklet seed type
     //zero elements are unused
    {
     { 0,    5.5,    15.0, 1.5,  2.0,  0,    1.5,  0.7  },//layer 1 z windows
     { 0,    3.5,    15.0, 1.25, 0,    0,    0,    0    },//layer 2 z windows
     { 0.7,  0,      9.0,  0,    0,    0,    0,    0    },//layer 3 z windows
     { 3.0,  7.0,    0,    0,    0,    0,    0,    3.0  },//layer 4 z windows
     { 3.0,  8.0,    0,    0,    0,    0,    0,    3.0  },//layer 5 z windows
     { 4.0,  9.5,    0,    0,    0,    0,    0,    0    } //layer 6 z windows
    },
    rphiMatchingWindowsDiskPS //first index (row) is disk number, second index (column) is tracklet seed type
     //zero elements are unused
    {
      { 0.2,    0,    0,    0,    0.1,  0,    0,    0.2    },//disk 1 rphi windows
      { 0.2,    0,    0,    0,    0.1,  0,    0.1,  0.2    },//disk 2 rphi windows
      { 0.25,   0,    0,    0.15, 0,    0.2,  0.15, 0.2    },//disk 3 rphi windows
      { 0.5,    0,    0,    0.2,  0,    0.3,  0.5,  0.2    },//disk 4 rphi windows
      { 0,      0,    0,    0.25, 0.1,  0.5,  0,    0      } //disk 5 rphi windows
    },
    rphiMatchingWindowsDisk2S //first index (row) is disk number, second index (column) is tracklet seed type
     //zero elements are unused
    {
      { 0.5,  0.8,  0,    0,    0.1,  0,    0,    0.5  },//disk 1 rphi windows
      { 0.5,  0.8,  0,    0,    0,    0.5,  0.15, 0.5  },//disk 2 rphi windows
      { 0.5,  0,    0,    0.15, 0,    0.2,  0.25, 0.5  },//disk 3 rphi windows
      { 0.5,  0,    0,    0.2,  0,    0.25, 0.5,  0.5  },//disk 4 rphi windows
      { 0,    0,    0,    0.4,  0.2,  0.4,  0,    0    } //disk 5 rphi windows
    },
    rMatchingWindowsDiskPS //first index (row) is disk number, second index (column) is tracklet seed type
     //zero elements are unused
    {
      { 0.5,    0,    0,    0,    0.5,    0,    0,    0.5    },//disk 1 r windows
      { 0.5,    0,    0,    0,    0.5,    0.5,  0.5,  0.5    },//disk 2 r windows
      { 0.5,    0,    0,    0.5,    0,    0.6,  0.8,  0.5    },//disk 3 r windows
      { 0.5,    0,    0,    0.8,    0,    1.0,  1.0,  0.5    },//disk 4 r windows
      { 0,      0,    0,    1.0,  0.5,    2.0,  0,    0      } //disk 5 r windows
    },
    rMatchingWindowsDisk2S //first index (row) is disk number, second index (column) is tracklet seed type
     //zero elements are unused
    {
      { 3.8,  3.8,  0,    0,    0,    0,    0,    3.8    },//disk 1 r windows
      { 3.8,  3.8,  0,    0,    0,    3.8,  3.4,  3.8    },//disk 2 r windows
      { 3.6,  0,    0,    3.6,  0,    3.6,  3.8,  3.8    },//disk 3 r windows
      { 3.6,  0,    0,    3.6,  0,    3.5,  3.8,  3.8    },//disk 4 r windows
      { 0,    0,    0,    3.6,  3.4,  3.7,  0,    0      } //disk 5 r windows
    }
   {}

   double phiMatchingWindowsBarrel[6][8];
   double zMatchingWindowsBarrel[6][8];
  
   double rphiMatchingWindowsDiskPS[5][8];
   double rphiMatchingWindowsDisk2S[5][8];

   double rMatchingWindowsDiskPS[5][8];
   double rMatchingWindowsDisk2S[5][8];

   ~TrackletWindows(){};


  private:
 };


}

#endif
