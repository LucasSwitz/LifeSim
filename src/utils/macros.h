#ifndef MACROS_DEF
#define MACROS_DEF

#define DEV_LOG(X)                                      \
do {                                                    \    
    DevelopmentOverlay::Instance()->GetLog()->AddLog(X); \
} while(0)

#endif