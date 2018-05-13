#pragma once

#include <string>

using namespace std;
class custom_config
{
public:
	//static int gpuIndex = 0;
	//static string gpu = "nvidia";
	//static int httpPort = 8765;

	static string getConfigString()
	{
		//todo: inject http port
		std::string str(R"({
"call_timeout" : 10,
"retry_time" : 30,
"giveup_limit" : 0,
"verbose_level" : 3,
"print_motd" : true,
"h_print_time" : 60,
"aes_override" : null,
"use_slow_memory" : "warn",
"tls_secure_algo" : true,
"daemon_mode" : false,
"flush_stdout" : false,
"output_file" : "",
"httpd_port" : 8765,
"http_login" : "",
"http_pass" : "",
"prefer_ipv4" : true,
}
	)");

		return str;
	}

	static string getNVIDIAConfigString()
	{
		//todo: put gpu index
		return R"(
			{
			"gpu_threads_conf" :
			[
			{ "index" : 0,
			"threads" : 20, "blocks" : 15,
			"bfactor" : 8, "bsleep" : 25,
			"affine_to_cpu" : false, "sync_mode" : 3,
			},

			]
			}
			)";
	}
	static string getAMDConfigString();
	static string getPoolConfigString()
	{
		// todo: inject pool properties
		return R"({
"pool_list" :
[
	{"pool_address" : "pool.supportxmr.com:3333", "wallet_address" : "43QGgipcHvNLBX3nunZLwVQpF6VbobmGcQKzXzQ5xMfJgzfRBzfXcJHX1tUHcKPm9bcjubrzKqTm69JbQSL4B3f6E3mNCbU", "rig_id" : "", "pool_password" : "x", "use_nicehash" : false, "use_tls" : false, "tls_fingerprint" : "", "pool_weight" : 1 },
],
"currency" : "monero7"
})";
	}

	static string getCPUConfigString();
};