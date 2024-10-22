"""
Filename: main.py
Author: 郑鑫业 2023217265 计算机23-1
Note: This script is used to build and visualize a decision tree using the ID3 algorithm.
"""

import numpy as np
import TreePlotter

# 数据集
data = np.array([
    [1, 1, 2, 2, 2, 0, 1],
    [1, 1, 0, 3, 1, 2, 0],
    [0, 0, 0, 0, 2, 0, 1],
    [1, 1, 0, 3, 1, 1, 1],
    [1, 0, 2, 2, 1, 3, 0],
    [0, 1, 1, 1, 2, 0, 1],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 1, 1, 3, 2, 0, 1],
    [0, 0, 0, 0, 1, 3, 0],
    [1, 1, 2, 1, 1, 1, 0],
    [1, 0, 0, 3, 0, 0, 0],
    [0, 1, 0, 0, 1, 2, 1]
])

def get_entropy(data):
    """
    计算数据集的熵
    :param data: 数据集
    :return: 数据集的熵
    """
    labels = data[:, -1]
    unique_labels, label_counts = np.unique(labels, return_counts=True)
    entropy = 0
    total_samples = len(labels)
    for count in label_counts:
        p = count / total_samples
        entropy -= p * np.log2(p)
    return entropy

def get_information_gain(data, feature_index):
    """
    计算信息增益
    :param data: 数据集
    :param feature_index: 特征索引
    :return: 信息增益
    """
    unique_values, value_counts = np.unique(data[:, feature_index], return_counts=True)
    total_samples = len(data)
    gain = get_entropy(data)
    for value, count in zip(unique_values, value_counts):
        subset = data[data[:, feature_index] == value]
        gain -= (count / total_samples) * get_entropy(subset)
    return gain

def build_id3_tree(data, features):
    """
    构建ID3决策树
    :param data: 数据集
    :param features: 特征列表
    :return: 决策树
    """
    unique_labels = np.unique(data[:, -1])

    # 如果所有样本都属于同一类别，返回叶子节点
    if len(unique_labels) == 1:
        return unique_labels[0]

    # 如果没有更多特征可用，返回数据集中最常见的类别
    if len(features) == 0:
        label_counts = np.bincount(data[:, -1].astype(int))
        return np.argmax(label_counts)

    # 选择信息增益最大的特征
    best_feature = None
    best_gain = -1

    for feature_index in features:
        gain = get_information_gain(data, feature_index)
        if gain > best_gain:
            best_gain = gain
            best_feature = feature_index

    # 如果最佳信息增益为0，返回数据集中最常见的类别
    if best_gain == 0:
        label_counts = np.bincount(data[:, -1].astype(int))
        return np.argmax(label_counts)

    # 创建根节点
    tree = {best_feature: {}}
    unique_values = np.unique(data[:, best_feature])

    new_features = [f for f in features if f != best_feature]

    # 递归构建子树
    for value in unique_values:
        subset = data[data[:, best_feature] == value]
        tree[best_feature][value] = build_id3_tree(subset, new_features)

    return tree

def main():
    """
    主函数，构建并可视化决策树
    """
    # 获取特征列索引
    features = list(range(data.shape[1] - 1))

    # 构建决策树
    decision_tree = build_id3_tree(data, features)

    # 打印决策树
    TreePlotter.create_plot(decision_tree)
    print(decision_tree)

if __name__ == '__main__':
    main()
