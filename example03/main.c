#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

// Until the server gives us the compositor, it will be NULL.
struct wl_compositor *compositor = NULL;

void on_global_registry(void *data, struct wl_registry *registry, uint32_t name,
                        const char *interface, uint32_t version) {
  // Identify compositor and save to variable.
  if (strcmp(interface, "wl_compositor") == 0) {
    compositor =
        wl_registry_bind(registry, name, &wl_compositor_interface, version);
  }
  printf("on_global_registry: %s\n", interface);
}

void on_global_registry_remove(void *data, struct wl_registry *registry,
                               uint32_t name) {
  printf("on_global_registry_remove\n");
}

int main(void) {
  struct wl_display *display = wl_display_connect(NULL);

  if (display) {
    printf("Ok\n");
  } else {
    printf("Error\n");
    wl_display_disconnect(display);
    return 0;
  }

  struct wl_registry *registry = wl_display_get_registry(display);
  struct wl_registry_listener listener = {
      .global = on_global_registry,
      .global_remove = on_global_registry_remove,
  };

  wl_registry_add_listener(registry, &listener, NULL);
  wl_display_dispatch(display);
  wl_display_roundtrip(display);

  // Check after waiting all queued request finished.
  if (compositor == NULL) {
    printf("Failed to get compositor\n");
  } else {
    printf("Got compositor\n");
  }

  wl_display_disconnect(display);

  return 0;
}