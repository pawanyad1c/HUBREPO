#include <signal.h>
#include <string.h>
#include <stdio.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <termio.h>
#include <fstream>
#include<pthread.h>
#include "plog/Log.h"
#include <sqlite3.h>
#include <math.h>
#include<time.h>
using namespace std;
using namespace plog;

#define FALSE         0
#define TRUE          1
#define RECEIPT_OK    3
#define RECEIPT_ERROR 4
#define SMS_MAX       10
#define MAX_SMS_TEXT  121
#define MAX_REV_TEXT  255
