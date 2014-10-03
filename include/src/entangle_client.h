#ifndef _ENTANGLE_CLIENT_H
#define _ENTANGLE_CLIENT_H

#include <memory>
#include <vector>

#include "libs/entangle-server/dopt_void_hook.h"
#include "libs/entangle-server/dopt_node.h"

namespace entangle {
	class EntangleClient : public OTVoidHook, public std::enable_shared_from_this<EntangleClient> {
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

			std::vector<std::string> get_log();
			void enq(std::string l);

		private:
			OTNode<EntangleClient> node;

			bool is_blank;
			std::vector<std::string> log;
	};
}

#endif
