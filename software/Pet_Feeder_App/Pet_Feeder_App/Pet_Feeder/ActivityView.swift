//
//  ActivityView.swift
//  Pet_Feeder
//
//  Created by 韩丽颖 on 2021/11/7.
//

import SwiftUI

struct Message: Codable {
    let msg: String
    let time: String
    let logID: Int
}

//struct Result: Codable {
//    var trackId: Int
//    var trackName: String
//    var collectionName: String
//}

struct ActivityView: View {
//    @State var results = [Result]()
    @State var messageList = [Message]()
    
    
    var body: some View {
        List(messageList, id: \.logID) { item in
                    VStack(alignment: .leading) {
                        Text(item.time)
                            .font(.headline)
                        Text(item.msg)
                    }
                }
                .onAppear(perform: loadData)
    }
    
    func loadData() {
        guard let url = URL(string: "http://172.91.84.234:5000/logs") else {
            print("Invalid URL")
            return
        }

        let request = URLRequest(url: url)

        URLSession.shared.dataTask(with: request) { data, response, error in
            if let data = data {
                if let decodedResponse = try? JSONDecoder().decode([Message].self, from: data) {
                    // we have good data = go back to the main thread
                    DispatchQueue.main.async {
                        // update our UI
                        self.messageList = decodedResponse
                    }

                    // everything is good, so we can exit
                    return
                }
            }

            // if we're still here it means there was a problem
            print("Fetch failed: \(error?.localizedDescription ?? "Unknown error")")
        }.resume()
    }
}

struct ActivityView_Previews: PreviewProvider {
    static var previews: some View {
        ActivityView()
    }
}
