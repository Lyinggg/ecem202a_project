//
//  Food.swift
//  Pet_Feeder
//
//  Created by 韩丽颖 on 2021/11/7.
//

import Foundation

class Food: ObservableObject {
    @Published var frequency = 12
    @Published var amount = 30
    @Published var amount_list = [10,20,30,40]
}
