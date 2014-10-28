#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#include <event2/event.h>
#else
#include <event.h>
#endif

#include <evhtp.h>


struct _SeafileSession;

typedef struct HttpServer {
    char *bind_addr;
    int bind_port;
    evbase_t *evbase;
    evhtp_t *evhtp;
    pthread_t thread_id;

    GHashTable *token_cache;
    pthread_mutex_t token_cache_lock; /* token -> username */

    GHashTable *perm_cache;
    pthread_mutex_t perm_cache_lock; /* repo_id:username -> permission */

    event_t *reap_timer;

    struct _SeafileSession *seaf_session;
} HttpServer;

HttpServer *
seaf_http_server_new (struct _SeafileSession *session);

void seaf_http_server_release (HttpServer *htp_server);

int
seaf_http_server_start (HttpServer *htp_server);

#endif
