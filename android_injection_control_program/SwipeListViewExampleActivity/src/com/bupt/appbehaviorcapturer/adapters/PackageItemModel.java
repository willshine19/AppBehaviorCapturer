package com.bupt.appbehaviorcapturer.adapters;

import java.util.ArrayList;

import android.content.Context;

/**
 * @author sang
 * 单例模式
 */
public class PackageItemModel {

	private ArrayList<PackageItem> list;
	private Context context;
	private static PackageItemModel singleton;
	
	private PackageItemModel() {
		this.list = new ArrayList<PackageItem>();
	}
	
	public static PackageItemModel getInstance() {
		if (singleton == null) {
			singleton = new PackageItemModel();
		}
		return singleton;
	}
	
	public ArrayList<PackageItem> getList() {
		return list;
	}
	
	public void add(PackageItem item) {
		list.add(item);
	}
	
	
}
