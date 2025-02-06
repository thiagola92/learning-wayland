#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <wayland-client-core.h>
#include <wayland-client-protocol.h>
#include <wayland-client.h>

void on_global_registry(void *data, struct wl_registry *registry, uint32_t name,
                        const char *interface, uint32_t version) {
  printf("on_global_registry: %s %d\n", interface, name);
}

void on_global_registry_remove(void *data, struct wl_registry *registry,
                               uint32_t name) {
  printf("on_global_registry_remove: %d\n", name);
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

  // Wayland works asynchronously thanks to handlers/listeners/callbacks.
  struct wl_registry *registry = wl_display_get_registry(display);
  struct wl_registry_listener listener = {
      .global = on_global_registry,
      .global_remove = on_global_registry_remove,
  };

  wl_registry_add_listener(registry, &listener, NULL);

  // After configure everything, we dispatch it.
  wl_display_dispatch(display);

  // Wait until Ctrl+C is pressed.
  pause();

  wl_display_disconnect(display);

  return 0;
}