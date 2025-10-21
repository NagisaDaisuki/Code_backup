#include <stdio.h>

// Define a debug logging macro
#define LOG_DEBUG(message)                                                     \
  fprintf(stderr, "DEBUG: %s:%d:%s(): %s\n", __FILE__, __LINE__, __func__,     \
          message)

void process_data() {
  LOG_DEBUG("Starting data processing...");
  // Simulate some work
  LOG_DEBUG("Data processing complete.");
}

int main(void) {
  LOG_DEBUG("Application started.");
  process_data();
  LOG_DEBUG("Application finished.");
  return 0;
}
