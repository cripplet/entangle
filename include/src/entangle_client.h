#ifndef _ENTANGLE_CLIENT_H
#define _ENTANGLE_CLIENT_H

#include "libs/entangle-server/dopt_void_hook.h"
#include "libs/entangle-server/dopt_node.h"

namespace entangle {
	class EntangleClient : public OTVoidHook {
		public:
			EntangleClient();

			// local invocation
			EntangleClient(std::string filename);

			// remote invocation
			EntangleClient(std::string hostname, size_t port);

			~EntangleClient();

			virtual void i(size_t pos, char c);
			virtual void e(size_t pos);

			size_t get_port();

		private:
			OTNode<EntangleClient> node;
			bool is_blank;
	};
}

#endif
