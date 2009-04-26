contents = {
	content = {
		id      = "p1_body";
		source  = "index.scm";
		filters = {
			filter[0] = {
				source      = "sxml";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p1_map";
		source  = "@work_dir@/maps/p1.map";
		filters = {
			filter[0] = {
				source      = "map";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p2_body";
		source  = "development.scm";
		filters = {
			filter[0] = {
				source      = "sxml";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p2_map";
		source  = "@work_dir@/maps/p2.map";
		filters = {
			filter[0] = {
				source      = "map";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "news_body";
		source  = "news.sxml";
		filters = {
			filter[0] = {
				source      = "sxml";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "news_map";
		source  = "@work_dir@/maps/news.map";
		filters = {
			filter[0] = {
				source      = "map";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

        content = {
                id      = "todos_body";
                source  = "todos.sxml";
                filters = {
                        filter[0] = {
                                source      = "sxml";
                                destination = "sxml";
                                parameters  = "";
                        };
                };
        };

        content = {
                id      = "todos_map";
                source  = "@work_dir@/maps/todos.map";
                filters = {
                        filter[0] = {
                                source      = "map";
                                destination = "sxml";
                                parameters  = "";
                        };
                };
        };

	content = {
		id      = "p3_body";
		source  = "downloads.scm";
		filters = {
			filter[0] = {
				source      = "sxml";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p3_map";
		source  = "@work_dir@/maps/p3.map";
		filters = {
			filter[0] = {
				source      = "map";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p4_body";
		source  = "installation.scm";
		filters = {
			filter[0] = {
				source      = "sxml";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

	content = {
		id      = "p4_map";
		source  = "@work_dir@/maps/p4.map";
		filters = {
			filter[0] = {
				source      = "map";
				destination = "sxml";
				parameters  = "";
			};
		};
	};

        content = {
                id     = "footer";
                source = "./footer.sxml";
                filters = {
                        filter[0] = {
                                source      = "sxml";
                                destination = "sxml";
                                parameters  = "";
                        };
                };
        };

        content = {
                id     = "header";
                source = "./header.sxml";
                filters = {
                        filter[0] = {
                                source      = "sxml";
                                destination = "sxml";
                                parameters  = "";
                        };
                };
        };
};
