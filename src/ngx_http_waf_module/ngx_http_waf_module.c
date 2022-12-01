#include <nginx.h>
#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

ngx_module_t ngx_http_waf_module;

static char *ngx_http_waf_init(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);
static ngx_int_t ngx_http_waf_handler(ngx_http_request_t *r);

static ngx_command_t ngx_http_waf_commands[] = {

    { ngx_string("hello_world"), /* directive */
      NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS, /* location context and takes
                                            no arguments*/
      ngx_http_waf_init, /* configuration setup function */
      0, /* No offset. Only one context is supported. */
      0, /* No offset when storing the module configuration on struct. */
      NULL},

    ngx_null_command /* command termination */
};

static ngx_http_module_t ngx_http_waf_module_ctx = {
  NULL,                                 /* preconfiguration */
  NULL,                                 /* postconfiguration */
  NULL,                                 /* create main configuration */
  NULL,                                 /* init main configuration */
  NULL,                                 /* create server configuration */
  NULL,                                 /* merge server configuration */
  NULL,                                 /* create location configuration */
  NULL                                  /* merge location configuration */
};

ngx_module_t ngx_http_waf_module = {
  NGX_MODULE_V1,
  &ngx_http_waf_module_ctx, /* module context */
  ngx_http_waf_commands,           /* module directives */
  NGX_HTTP_MODULE,                 /* module type */
  NULL,                            /* init master */
  NULL,                            /* init module */
  NULL,                            /* init process */
  NULL,                            /* init thread */
  NULL,                            /* exit thread */
  NULL,                            /* exit process */
  NULL,                            /* exit master */
  NGX_MODULE_V1_PADDING
};

static ngx_int_t ngx_http_waf_handler(ngx_http_request_t *r)
{
  if (r->main->internal) {
    return NGX_DECLINED;
  }

  r->main->internal = 1;

  ngx_table_elt_t *h;
  h = ngx_list_push(&r->headers_out.headers);
  h->hash = 1;
  ngx_table_elt_t *ua = r->headers_in.user_agent;
  ngx_str_set(&h->key, "X-NGINX-Tutorial");
  ngx_str_set(&h->value, ua->value.data);
  if(1) {
    return NGX_HTTP_FORBIDDEN;
  }

  return NGX_DECLINED;
}

static char *ngx_http_waf_init(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    ngx_http_core_loc_conf_t *clcf; /* pointer to core location configuration */

    /* Install the hello world handler. */
    clcf = ngx_http_conf_get_module_loc_conf(cf, ngx_http_core_module);
    clcf->handler = ngx_http_waf_handler;

    return NGX_CONF_OK;
}