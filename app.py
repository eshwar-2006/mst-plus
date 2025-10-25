import streamlit as st
from subprocess import run, PIPE

st.title("Extended MST: Nodes + Edges Weights")

num_nodes = st.number_input("Number of nodes", min_value=1, value=4)
num_edges = st.number_input("Number of edges", min_value=1, value=5)

st.write("Enter edge data in format: u v edge_weight node_weight_u node_weight_v")
edge_data = st.text_area("Edges", "1 2 10 3 4\n2 3 5 4 2")

if st.button("Compute MST"):
    input_str = f"{num_nodes} {num_edges}\n{edge_data}"
    result = run(['./mst_exec'], input=input_str.encode(), stdout=PIPE)
    st.success(result.stdout.decode())
