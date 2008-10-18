
/*
   Copyright (C) 2007 by David White <dave.net>
   Part of the Silver Tree Project

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License version 2 or later.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY.

   See the COPYING file for more details.
*/
#ifndef WML_NODE_HPP_INCLUDED
#define WML_NODE_HPP_INCLUDED

#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <vector>

#include "wml_node_fwd.hpp"

namespace wml
{

class schema;

class node
{
public:
	explicit node(const std::string& name) : name_(name), schema_(NULL)
	{}

	const std::string& name() const { return name_; }

	const std::string& operator[](const std::string& key) const;
	const std::string& attr(const std::string& key) const;
	void set_attr(const std::string& key, const std::string& value);
	void set_or_erase_attr(const std::string& key, const std::string& value);

	bool has_attr(const std::string& key) const;

	typedef std::map<std::string,std::string> attr_map;
	typedef attr_map::const_iterator const_attr_iterator;
	const_attr_iterator begin_attr() const;
	const_attr_iterator end_attr() const;

	typedef std::multimap<std::string,boost::shared_ptr<node> >::
			iterator child_iterator;
	typedef std::multimap<std::string,boost::shared_ptr<node> >::
			const_iterator const_child_iterator;

	typedef std::pair<child_iterator,child_iterator> child_range;
	typedef std::pair<const_child_iterator,const_child_iterator>
	        const_child_range;

	typedef std::vector<boost::shared_ptr<node> >::iterator
			all_child_iterator;
	typedef std::vector<boost::shared_ptr<node> >::const_iterator
			const_all_child_iterator;

	child_iterator begin_child(const std::string& key);
	const_child_iterator begin_child(const std::string& key) const;

	child_iterator end_child(const std::string& key);
	const_child_iterator end_child(const std::string& key) const;

	child_range get_child_range(const std::string& key);
	const_child_range get_child_range(const std::string& key) const;

	all_child_iterator begin_children();
	const_all_child_iterator begin_children() const;

	all_child_iterator end_children();
	const_all_child_iterator end_children() const;

	void add_child(boost::shared_ptr<node> child);

	const_node_ptr get_child(const std::string& key) const;
	node_ptr get_child(const std::string& key);

	void clear_attr();
	void clear_children();
	void clear_children(const std::string& name);
	void erase_child(const boost::shared_ptr<node>& child_node);

	void set_comment(const std::string& comment);
	const std::string& get_comment() const;
	void set_attr_comment(const std::string& name, const std::string& comment);
	const std::string& get_attr_comment(const std::string& name) const;

	const schema* get_schema() const { return schema_; }
	void set_schema(const schema* s) { schema_ = s; }

private:
	std::string name_;
	attr_map attr_;
	std::multimap<std::string,boost::shared_ptr<node> > childmap_;
	std::vector<boost::shared_ptr<node> > children_;

	const schema* schema_;

	//comment data
	std::string comment_;
	attr_map attr_comments_;
};

}

#endif
