#include <stdio.h>
#include <wayland-client-core.h>
#include <wayland-client.h>

int main(void) {
  struct wl_display *display = wl_display_connect(NULL);

  if (display) {
    printf("Ok\n");
  } else {
    printf("Error\n");
  }

  // Error or not, we need to disconnect to free memory.
  wl_display_disconnect(display);

  return 0;
}