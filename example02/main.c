#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

void on_global_registry(void *data, struct wl_registry *registry, uint32_t name,
                        const char *interface, uint32_t version) {
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

  // How everything works asynchronously, we may use this function to block
  // until all queued request are processed by the server.
  wl_display_roundtrip(display);

  wl_display_disconnect(display);

  return 0;
}